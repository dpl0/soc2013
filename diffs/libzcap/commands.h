/* 
	This is a list of all the capsizumized zlib interfaces.
	Every one of the capsicumized functions will have a define.
	This list is taken from zlib.h, in this same directory.

	All this defines represent the commands passed to the real
	zlib listening through a program, and it will recognize them.
	Also, the defines have been checked for not being duplicates.

	Since the only things that we can Capsicumize are: deflate()
	and inflate(), we only have to care about sending those to 
	commands (related to the basic functions, and utility functions.

*/

#define MAXLEN (5*1024)

#define ZCAPCMD_DEFLATEINIT			0
#define ZCAPCMD_DEFLATE				1
#define ZCAPCMD_DEFLATEEND			2
#define ZCAPCMD_INFLATEINIT			3
#define ZCAPCMD_INFLATE				4
#define ZCAPCMD_INFLATEEND			5

/* Advanced functions */
#define ZCAPCMD_DEFLATESETDICTIONARY 	6
#define ZCAPCMD_DEFLATECOPY 			7
#define ZCAPCMD_DEFLATERESET 			8
#define ZCAPCMD_DEFLATEPARAMS 		9
#define ZCAPCMD_DEFLATETUNE 			10
#define ZCAPCMD_DEFLATEBOUND 			11
#define ZCAPCMD_DEFLATEPENDING 		12
#define ZCAPCMD_DEFLATEPRIME 			13
#define ZCAPCMD_DEFLATESETHEADER 		14
#define ZCAPCMD_INFLATEINIT2 			15
#define ZCAPCMD_INFLATESETDICTIONARY 	16
#define ZCAPCMD_INFLATEGETDICTIONARY 	17
#define ZCAPCMD_INFLATESYNC 			18
#define ZCAPCMD_INFLATECOPY 			19
#define ZCAPCMD_INFLATERESET 			20
#define ZCAPCMD_INFLATERESET2 			21
#define ZCAPCMD_INFLATEPRIME 			22
#define ZCAPCMD_INFLATEMARK 			23
#define ZCAPCMD_INFLATEGETHEADER 		24
#define ZCAPCMD_INFLATEBACKINIT 		25
#define ZCAPCMD_INFLATEBACK 			26
#define ZCAPCMD_INFLATEBACKEND		27
#define ZCAPCMD_ZLIBCOMPILEFLAGS		28

/* utility functions */
#define ZCAPCMD_COMPRESSBOUND		29

/* gzip file access functions */
#define ZCAPCMD_GZOPEN				30
#define ZCAPCMD_GZBUFFER				31
#define ZCAPCMD_GZSETPARAMS			32
#define ZCAPCMD_GZREAD				33
#define ZCAPCMD_GZWRITE				34
#define ZCAPCMD_GZPRINTF				35
#define ZCAPCMD_GZPUTS				36
#define ZCAPCMD_GZGETS				46
#define ZCAPCMD_GZPUTC				47
#define ZCAPCMD_GZGETC				48
#define ZCAPCMD_GZUNGETC				49
#define ZCAPCMD_GZFLUSH				50
#define ZCAPCMD_GZSEEK				51
#define ZCAPCMD_GZREWIND				52
#define ZCAPCMD_GZTELL				53
#define ZCAPCMD_GZOFFSET				54
#define ZCAPCMD_GZEOF				55
#define ZCAPCMD_GZDIRECT				56
#define ZCAPCMD_GZCLOSE_R			57
#define ZCAPCMD_GZCLOSE_W			58
#define ZCAPCMD_GZERROR				59
#define ZCAPCMD_GZCLEARERR			60

/* checksum functions */
#define ZCAPCMD_ADLER32				61
#define ZCAPCMD_ADLER32_COMBINE		62
#define ZCAPCMD_CRC32				63
#define ZCAPCMD_CRC32_COMBINE		64
