///////////////////////////////////////////////////////////////////////////////
//
/// \file       file_io.h
/// \brief      I/O types and functions
//
//  Author:     Lasse Collin
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

// Some systems have suboptimal BUFSIZ. Use a bit bigger value on them.
// We also need that IO_BUFFER_SIZE is a multiple of 8 (sizeof(uint64_t))
#if BUFSIZ <= 1024
#	define IO_BUFFER_SIZE 8192
#else
#	define IO_BUFFER_SIZE (BUFSIZ & ~7U)
#endif


/// is_sparse() accesses the buffer as uint64_t for maximum speed.
/// Use an union to make sure that the buffer is properly aligned.
typedef union {
	uint8_t u8[IO_BUFFER_SIZE];
	uint32_t u32[IO_BUFFER_SIZE / sizeof(uint32_t)];
	uint64_t u64[IO_BUFFER_SIZE / sizeof(uint64_t)];
} io_buf;


/// \brief      Initialize the I/O module
extern void io_init(void);


/// \brief      Disable creation of sparse files when decompressing
extern void io_no_sparse(void);


/// \brief      Open the source file
extern file_pair *io_open_src(const char *src_name);


/// \brief      Open the destination file
extern bool io_open_dest(file_pair *pair);


/// \brief      Closes the file descriptors and frees possible allocated memory
///
/// The success argument determines if source or destination file gets
/// unlinked:
///  - false: The destination file is unlinked.
///  - true: The source file is unlinked unless writing to stdout or --keep
///    was used.
extern void io_close(file_pair *pair, bool success);


/// \brief      Reads from the source file to a buffer
///
/// \param      pair    File pair having the source file open for reading
/// \param      buf     Destination buffer to hold the read data
/// \param      size    Size of the buffer; assumed be smaller than SSIZE_MAX
///
/// \return     On success, number of bytes read is returned. On end of
///             file zero is returned and pair->src_eof set to true.
///             On error, SIZE_MAX is returned and error message printed.
extern size_t io_read(file_pair *pair, io_buf *buf, size_t size);


/// \brief      Read from source file from given offset to a buffer
///
/// This is remotely similar to standard pread(). This uses lseek() though,
/// so the read offset is changed on each call.
///
/// \param      pair    Seekable source file
/// \param      buf     Destination buffer
/// \param      size    Amount of data to read
/// \param      pos     Offset relative to the beginning of the file,
///                     from which the data should be read.
///
/// \return     On success, false is returned. On error, error message
///             is printed and true is returned.
extern bool io_pread(file_pair *pair, io_buf *buf, size_t size, off_t pos);


/// \brief      Writes a buffer to the destination file
///
/// \param      pair    File pair having the destination file open for writing
/// \param      buf     Buffer containing the data to be written
/// \param      size    Size of the buffer; assumed be smaller than SSIZE_MAX
///
/// \return     On success, zero is returned. On error, -1 is returned
///             and error message printed.
extern bool io_write(file_pair *pair, const io_buf *buf, size_t size);


/// \brief      Open all the files as needed.
///
/// \param      filenames    Array containing all the filenames to be open.
/// \param      files     Number of files to open.
///
/// \return     Returns an array of file_pairs.
extern file_pair ** io_open_files(char *filenames[], int  files);


#if defined(CAPSICUM)
/// \brief      Limits fd using FreeBSD's Capsicum framework.
///
/// \param      fd    File descriptor to limit.
extern void limitpair(file_pair *pair);

/// \brief      Enters Capability mode, and limit basic fds.
extern void capsicum_enter(void);
#endif
