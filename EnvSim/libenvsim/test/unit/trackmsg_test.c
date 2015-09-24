//     Project: EnvSim
//      Module: libenvsim / test
// Description: Unit tests for module trackmsg.c
//
// History:
// - 22.09.15, J. Kastner: initial version

#include <check.h>
#include <kcg_types.h>
#include <trackmsg.h>
#include "trackmsg.h"

START_TEST(test_es_write_next_balise_message) {
  CompressedBaliseMessage_TM src = {
  .Header = {
    .m_dup = 1,
    .m_mcount = 2,
    .m_version = 3,
    .n_pig = 4,
    .n_total = 5,
    .nid_bg = 6,
    .nid_c = 7,
    .q_link = 8,
    .q_media = 9,
    .q_updown = 10 }
  };

    src.Messages.PacketHeaders[0].valid = kcg_true;
    src.Messages.PacketHeaders[1].valid = kcg_true;
    src.Messages.PacketHeaders[2].valid = kcg_false;
    src.Messages.PacketData[42] = 42;

    CompressedBaliseMessage_TM tgt;

    es_queue_balise_message(&src);

    es_write_next_balise_message(&tgt);
    ck_assert_int_eq(7,tgt.Header.nid_c);
    ck_assert(tgt.Messages.PacketHeaders[0].valid);
    ck_assert(tgt.Messages.PacketHeaders[1].valid);
    ck_assert(! tgt.Messages.PacketHeaders[2].valid);
    ck_assert_int_eq(42, tgt.Messages.PacketData[42]);


} END_TEST;


START_TEST(test_es_add_triggered_balise_message) {
    CompressedBaliseMessage_TM bmsg1 = { .Header.nid_c = 1};
    CompressedBaliseMessage_TM bmsg2 = { .Header.nid_c = 2};
    CompressedBaliseMessage_TM bmsg3 = { .Header.nid_c = 3};

    es_TrackMessages track;
    track.bmsgs = NULL;

    es_add_triggered_balise_message(&track,101.5,&bmsg2);
    ck_assert_int_eq(2, ((es_TriggeredBaliseMessage*)track.bmsgs->data)->msg.Header.nid_c);

    es_add_triggered_balise_message(&track,42.0,&bmsg1);
    ck_assert_int_eq(1, ((es_TriggeredBaliseMessage*)track.bmsgs->data)->msg.Header.nid_c);
    ck_assert_int_eq(2, ((es_TriggeredBaliseMessage*)track.bmsgs->tail->data)->msg.Header.nid_c);

    es_add_triggered_balise_message(&track,1234.5,&bmsg3);
    ck_assert_int_eq(1, ((es_TriggeredBaliseMessage*)track.bmsgs->data)->msg.Header.nid_c);
    ck_assert_int_eq(2, ((es_TriggeredBaliseMessage*)track.bmsgs->tail->data)->msg.Header.nid_c);
    ck_assert_int_eq(3, ((es_TriggeredBaliseMessage*)track.bmsgs->tail->tail->data)->msg.Header.nid_c);

  } END_TEST;


TCase* tc_trackmsg() {
  TCase *tc = tcase_create("trackmsg");

  tcase_add_test(tc, test_es_write_next_balise_message);
  tcase_add_test(tc, test_es_add_triggered_balise_message);

  return tc;
}