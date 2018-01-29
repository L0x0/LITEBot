# LITEBot
Wasted Time

LITEBot is an exercise in wasted time and effort; a terrible idea realized by an amateur attempt at developing a working C/C++ program. The program had a simple purpose of being able to read data on file or in memory and store some basic information about each byte read; the previous byte (if not element 0), the following byte (if not element end) and the encoding of the byte; then store the information in a coherent manner that could be retrieved later.

pthreads was chosen for cross-compatibility for Windows and ARM devices.  The pthreads version used for Windows was obtained and compiled according to instructions found on Sourcefourge.  The android version uses the existing <pthread.h> lib.

SQLITE was chosen as the database solution because of its' simplicity.  The windows version of SQLITE was compiled in the MSVS 2015 dev environment (windows 8.1) with no declared options.  The android version was compiled using gcc from the command line on a rooted ARM device with the option -DHASCHRNULL=0

One should assume both pthreads and SQLITE compiled for Windows were not correctly compiled as the developer has nfc what he was doing.

I place ye here LITEBot, far away but not entirely deleted.  
