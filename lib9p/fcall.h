#ifndef FCALL_H
#define FCALL_H

readonly static String8 version9p = str8litc("9P2000");

#define MAXWELEM 16

typedef struct Qid Qid;
struct Qid {
	u32 type;
	u32 vers;
	u64 path;
};

typedef struct Fcall Fcall;
struct Fcall {
	u32 type;
	u32 tag;
	u32 fid;
	u32 msize;               /* Tversion, Rversion */
	String8 version;         /* Tversion, Rversion */
	u32 oldtag;              /* Tflush */
	String8 ename;           /* Rerror */
	Qid qid;                 /* Rattach, Ropen, Rcreate */
	u32 iounit;              /* Ropen, Rcreate */
	Qid aqid;                /* Rauth */
	u32 afid;                /* Tauth, Tattach */
	String8 uname;           /* Tauth, Tattach */
	String8 aname;           /* Tauth, Tattach */
	u32 perm;                /* Tcreate */
	String8 name;            /* Tcreate */
	u32 mode;                /* Topen, Tcreate */
	u32 newfid;              /* Twalk */
	u32 nwname;              /* Twalk */
	String8 wname[MAXWELEM]; /* Twalk */
	u32 nwqid;               /* Rwalk */
	Qid wqid[MAXWELEM];      /* Rwalk */
	u64 offset;              /* Tread, Twrite */
	u32 count;               /* Tread, Rread, Twrite, Rwrite */
	String8 data;            /* Rread, Twrite */
	String8 stat;            /* Rstat, Twstat */
};

typedef struct Dir Dir;
struct Dir {
	/* system-modified data */
	u32 type; /* server type */
	u32 dev;  /* server subtype */
	/* file data */
	Qid qid;      /* unique id from server */
	u32 mode;     /* permissions */
	u32 atime;    /* last read time */
	u32 mtime;    /* last write time */
	u64 len;      /* file length */
	String8 name; /* last element of path */
	String8 uid;  /* owner name */
	String8 gid;  /* group name */
	String8 muid; /* last modifier name */
};

enum {
	Tversion = 100,
	Rversion = 101,
	Tauth = 102,
	Rauth = 103,
	Tattach = 104,
	Rattach = 105,
	Rerror = 107,
	Tflush = 108,
	Rflush = 109,
	Twalk = 110,
	Rwalk = 111,
	Topen = 112,
	Ropen = 113,
	Tcreate = 114,
	Rcreate = 115,
	Tread = 116,
	Rread = 117,
	Twrite = 118,
	Rwrite = 119,
	Tclunk = 120,
	Rclunk = 121,
	Tremove = 122,
	Rremove = 123,
	Tstat = 124,
	Rstat = 125,
	Twstat = 126,
	Rwstat = 127,
};

static u32 fcallsize(Fcall fc);
static String8 fcallencode(Arena *a, Fcall fc);
static Fcall fcalldecode(String8 msg);
static u32 dirsize(Dir d);
static String8 direncode(Arena *a, Dir d);
static Dir dirdecode(String8 msg);

#endif /* FCALL_H */
