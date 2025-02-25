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

This version was created with Visual Studion 2022 (VS22).  It was compiled with the following properties:
  - Windows SDK Version: 10.0.xxxxx (latest)
  - Platfor Toolset: visual Studio 2022 (latest)
  - MFC: Use MFC in a Shared DLL
  - Character Set:  Use Unicode Character Set
  - Precompiled Header:  Not Using Precompiled Headers
  - Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 (the last one produced) was used to prepare the help
file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

Wix is used to create the &lt;AppName&gt;.msi file.  WixApp (one of my applications, see git) was used
to produce the product.wxs file.

Note:  In order to avoid hickups during the compilation/link process make sure the VS22 dependencies are
set so the projects are produced in the proper order.

## Prerequisites

Windows 7 or above.  visual Studio 2022 or above.  The WiX Toolset must be installed in Visual Studio.
The "HTML Help Workshop" (google it) must be installed on the PC.

### Installing

Execute the msi file to install the app.

## Updates

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

