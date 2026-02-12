# RACES Interface App

Microsoft Access interface is a little tricky to program (in Basic of all things).  Some time ago I
found a way to read and write to the db.accdb file.  Since I was just about to change the user
interface I decided to try doing it in c++.  This app is the result.

This is a dialog app, in the sense that when it starts it shows a dialog box with all the fields
needed to describe a RACES member to the database.  But of course it is not that simple.  There
are a least four different group(s) that we need an interface too:
  - A New Member, i.e. a blank slate
  - The current members
  - The former members
  - The former members that have been former members long enough to delete them from the database

Since a database is useful for looking up information and for editing information we would like to
avoid editing a database entry when all we want is to view the entry.  So just selecting a member
in the drop down list will populate the dialog box in a read only manner.  To edit one must select
the Edit tool bar entry (a pencil).  The read only mechanism works with each sub group of the
membership.  Selecting New member puts the app in editable mode.

When a former member has been the database as a former member for sufficient time the trashcan
toolbar command will mark the member to be removed later.  Next to the trashcan command is the
"Remove Dead Records" command.  One of the issues with a relational database is that one record
may be referenced in multiple records.  A dead record is a record that is not referenced in any
records thus it may be marked to be removed later.  Deleting a former member may create some dead
records so running the "Remove Dead Records" command is usually wise.

The toolbar has an Update DB & Exit command (which is the rightmost icon).  If there have been no
changes in the application, the command immediately exits.  If there have been changes then a
dialog box asks if an update to the external database is to be allowed.  Answer no and the app
exits.  Answer yes and the app will update the file with the changes made within the app.

## Getting Started

The application is built with Visual Studio 2022 (VS22).  It was compiled with the following
properties:

  o Windows Latest SDK Version
  o Platfor Toolset: visual Studio 2022
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set
  o Built for the 64 bit (x64) platform because ODBC is now only available in the x64 platform
  o Additional Include Directories:
    * $(ProjectDir)
    * $(SolutionDir)..\..\Library\Library.prj\
    * $(SolutionDir)..\..\Library\DocView\
  o  Precompiled Header:  Not Using Precompiled Headers
  o  Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 was used to prepare the help file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

The Installer requires the Wix, HeatWave and NuGet-Tools Extensions to VS22.  WixApp (one of my
applications, see git) was used to produce the product.wxs file.

### Prerequisites

The WiX, HeatWave, NuGet-Tools Toolsets must be installed in Visual Studio.
The "HTML Help Workshop" (google it) must be installed.  Visual Studio 2022 or later.

### Installing

Execute the msi file to install the app.

## Updates

### Update 2/10/26

Build for the 64 bit platform.  Upgraded Wix to HeatWave version 4.
Prior to this version a Win32 platform was used since the 2010 Access Runtime supported both 32 bit
and 64 bit drivers.  But try as I did, I could not get the 2010 32 bit Access Runtime to install on
my laptop.  The solution was to build for the 64 bit platform and load the 2016 Access Runtime
(64 bit).

### Update 2/2/26

The Microsoft Access Runtime may only be loaded into my laptop as a 64 bit application since the
OS is 64 bit.  This was a dilemma as I have only used the compiler in 32 bit (or Win32) mode.  Many
changes in the library due to incompatible sizes (usally easily fixed with casts) but the wix
installer gave many more problems.  Nevertheless, compiling the app in 64 bit mode solved the issue
with the runtime.

### Update 1/12/26

Updated RACESdb Library using CodeGen.

### Update 1/10/26

Added "Non-Responder" option to Priority or Availability field.

### Update 10/21/25

Factored library into three parts, Library, Dialog, DocView.

### Update 10/17/25a

Added an extension of the dialog's InitInstance function that executes after the window is
initialized.  The extension executes as the result of a message posted from the InitInstance
function.  This allows the Puppy picture to be displayed, go figure...

### Update 10/17/25

Added a Save Record button, allow new record addition upon startup of App.

Factoring of Library for Doc/View, Dialog and general purpose modules.  Probably not completed.

### Update 9/19/25

Changes to accomodate modifications to ExpandableP.

### Update 7/7/25

Update Database objects to suppress memory leak reporting.  Factored IniFile into three classes.

### Update 6/23/25

Work on the memory leak problem.  Mostly it was a Visual Studio problem with false positives
that occur before all the static variables and objects release their storage.  Also found a
couple of records that were saved with labels, yuk.

### Update 6/20/25

Big hole in viewing records is plugged.

### Update 6/19/25

Corrected problem with empty fields in records.

### update 4/3/25

Corrected Update for new member.

### Update 3/20/25

Missed some fields in the save member function.

### Update 3/13/25

Date range test modified to include 1961 to 2059.

### Update 3/12/25

Modify command to toggle saving record changes.

### Update 3/8/25

Fix Read Only stuck bug.  Allow modifying start date.

### Update 3/5/25

Add MS Access compact to the App.  The App starts the Access app via the command line with a
/compact command line argument.

### Update 3/1/25

Rearranged the toolbar commands.  Fixed some find options.  Start the help document.

### Update 2/28/25

Add browse and find commands.

### Update 2/24/25

Add Combo Boxes to Street Addresses (Street, Unit Number) and Zip codes (City, State, Zip).  Added
labels to fields with no text description.  The labels disappear when entry into field is started.

The drop down lists for the combo boxes are filled in on the fly so that changes in one combo box
are reflected in other combo boxes.

### Update

Set default start date to today for new member.

### Update 2/18/25

Modified the handling of the dates in the date period filter.

### Update 2/17/25

Added a Former Member Report with date period filter.

### Update 2/9/25

Finished 10 Reports all but one verified.  Sent eMail with Everbridge report to board and ask them
to verify it will import into Everbridge.  We'll see if that effort works.

### Update 2/7/25

Add Three of several reports.  More to come.

### Update 2/4/25

Change names from RacesNew to RacesApp.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details



