#ifndef GLOBALS__H
#define GLOBALS__H

extern status_t status;

extern status_t (*pExport[]) (ADT_Array_t *, string);

extern status_t (*MP3_printer[]) (ADT_MP3_t *, FILE *);

extern export_t export_id;

#endif
