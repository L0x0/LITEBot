# LITEBot

pthreads was chosen for cross-compatibility for Windows and ARM devices.  The pthreads version used for Windows was obtained and compiled according to instructions found on Sourcefourge.  The android version uses the existing <pthread.h> lib.

SQLITE was chosen as the database solution because of its' simplicity.  The windows version of SQLITE was compiled in the MSVS 2015 dev environment (windows 8.1) with no declared options.  The android version was compiled using gcc command line on a rooted ARM device with the option -DHASCHRNULL=0

---To compile in MSVS:

Unzip the LITEBot and _includes folder to c:\LITEBot\.

Open MSVS and select File->New->Project from Existing Code

Choose Project Type Visual C++

Choose the folder 'LITEBot\LITEBot' as the Project File Location

Make sure 'Add files to the project from these folders' is checked

Select 'Add' and select the _includes folder

Select Project Type 'Console Application Project'

No defines are necessary.

Navigate to Project->LITEBot Properties

Navigate to Configuration Properties->Linker->Input

at the end of Additional Dependencies add 'pthreadVC2.lib; ws2_32.lib;' to the declared libraries.

Right click 'Source Files' in the Solution Explorer

Select Add->Existing Item

Select both pthreadVC2.lib and sqlite3.lib

The project should now Build and Run successfully.  

---To compile on an Android device using C4Droid + GCC plugin (Found on the Google Play Store) :

Create a folder in 'Device Storage' and in it place the LITEBot and _includes folder 

Open C4Droid

Choose 'Open' and select the litebot.h file.

Tap and hold 'Compile'

Choose 'Compile multiple source code files (simple)'

add '../_includes/_andr/sqlite3.o' ahead of litebot.cpp

Compile and run.
