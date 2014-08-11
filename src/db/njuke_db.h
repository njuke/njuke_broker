#ifndef NJUKE_DB_H
#define NJUKE_DB_H


#include "njuke_types.h"


/* Abstract interface for an event database. */

/* Opaque handle. */
struct njuke_db;

/* Connect to a database. Different kinds will require different parameters. */
struct njuke_db *njuke_db_connect(int narg, ...);

/* Add an event. Returns event number. */
int64_t njuke_db_add_event(struct njuke_db *db, struct njuke_event *event);

/* Remove an event. */
int njuke_db_remove_event(struct njuke_db *db, unsigned long event_id);

/* Get an event. */
struct njuke_event *njuke_db_get_event(struct njuke_db *db, char *name);

/* Increment th vote count for a song. */
int njuke_db_add_vote(struct njuke_db *db, unsigned long event_id,
                      unsigned long song_id);

/* Get the status for an event. */
struct njuke_event *njuke_db_get_votes(struct njuke_db *db,
                                       unsigned long event_id);


#endif
