The benefits of virtual memory are attractive, but is the scheme practical? At one
time, there was considerable debate on this point, but experience with numerous
operating systems has demonstrated beyond doubt that virtual memory does work.
Accordingly, virtual memory, based on either paging or paging plus segmentation, has
become an essential component of contemporary operating systems. To understand the key issue and why virtual memory was a matter of much
debate, let us examine again the task of the OS with respect to virtual memory. Consider a large process, consisting of a long program plus a number of arrays of data.
Over any short period of time, execution may be confined to a small section of the
program (e.g., a subroutine) and access to perhaps only one or two arrays of data. If
this is so, then it would clearly be wasteful to load in dozens of pieces for that process
when only a few pieces will be used before the program is suspended and swapped
out. We can make better use of memory by loading in just a few pieces. Then, if the
program branches to an instruction or references a data item on a piece not in main
memory, a fault is triggered. This tells the OS to bring in the desired piece.
Thus, at any one time, only a few pieces of any given process are in memory, and
therefore more processes can be maintained in memory. Furthermore, time is saved
because unused pieces are not swapped in and out of memory. However, the OS must
be clever about how it manages this scheme. In the steady state, practically all of main
memory will be occupied with process pieces, so the processor and OS have direct
access to as many processes as possible. Thus, when the OS brings one piece in, it must
throw another out. If it throws out a piece just before it is used, then it will just have to
go get that piece again almost immediately. Too much of this leads to a condition known
as thrashing: The system spends most of its time swapping pieces rather than executing
instructions. The avoidance of thrashing was a major research area in the 1970s and led
to a variety of complex but effective algorithms. In essence, the OS tries to guess, based
on recent history, which pieces are least likely to be used in the near future.
This reasoning is based on belief in the principle of locality, which was introduced in Chapter 1 (see especially Appendix 1A). To summarize, the principle of
locality states that program and data references within a process tend to cluster.
Hence, the assumption that only a few pieces of a process will be needed over a short
period of time is valid. Also, it should be possible to make intelligent guesses about
which pieces of a process will be needed in the near future, which avoids thrashing.
The principle of locality suggests that a virtual memory scheme may be effective. For virtual memory to be practical and effective, two ingredients are needed.
First, there must be hardware support for the paging and/or segmentation scheme to
be employed. Second, the OS must include software for managing the movement of
pages and/or segments between secondary memory and main memory. In this section,
we will examine the hardware aspect and look at the necessary control structures,
which are created and maintained by the OS but are used by the memory management hardware. An examination of the OS issues will be provided in the next section.
