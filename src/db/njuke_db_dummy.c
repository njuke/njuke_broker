#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "njuke_types.h"
#include "njuke_db.h"


/* This dummy just holds the events in memory. */
struct njuke_db {
        struct njuke_list_head events;
};

/* Opens the database which contains an event playing one song. */
struct njuke_db *njuke_db_connect(int narg, ...)
{
        struct njuke_db *db;
        struct njuke_event *event;
        struct njuke_song *song;

        db = malloc(sizeof(*db));
        njuke_list_init(&db->events);
        song = njuke_song_create("song", "artist");
        event = njuke_event_create("dummy event");
        njuke_list_add(&song->_list, &event->songs);
        njuke_list_add(&event->_list, &db->events);
        return db;
}

int64_t njuke_db_add_event(struct njuke_db *db, struct njuke_event *event)
{
        return 0;
}

int njuke_db_remove_event(struct njuke_db *db, unsigned long event_id)
{
        return 0;
}

struct njuke_event *njuke_db_get_event(struct njuke_db *db, char *name)
{
        struct njuke_event *event;
        int match = 0;

        NJUKE_LIST_FOR_EACH_ENTRY(event, &db->events, _list) {
                match = !strcmp(event->name, name);
                if (match) break;
        }
        return (match) ? event : NULL;
}

int njuke_db_add_vote(struct njuke_db *db, unsigned long event_id,
                unsigned long song_id)
{
        struct njuke_event *event;
        struct njuke_song *song;
        int match = 0;

        /* Find the event. */
        NJUKE_LIST_FOR_EACH_ENTRY(event, &db->events, _list) {
                match = (event->id == event_id);
                if (match) break;
        }
        if (!match) goto fail;
        /* Find the song. */
        NJUKE_LIST_FOR_EACH_ENTRY(song, &event->songs, _list) {
                match = (song->id == song_id);
                if (match) break;
        }
        if (!match) goto fail;
        song->votes++;
        return 0;
 fail:
        return -1;
}

struct njuke_event *njuke_db_get_votes(struct njuke_db *db, unsigned long event_id)
{
        /* TODO: Implement. */
        return NULL;
}
