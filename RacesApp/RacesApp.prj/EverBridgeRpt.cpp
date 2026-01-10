// EverBridge Report



#include "pch.h"
#include "EverBridgeRpt.h"
#include "Database.h"
#include "MemberList.h"
#include "Utility.h"

//#include "MessageBox.h"         // Debugging


/*
//First Name,Middle Initial,Last Name,Suffix,External ID,                                     // 5
//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                          // 6
//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,         // 6
//Country 1,Latitude 1,Longitude 1,Location Id 1,                                             // 4
//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,         // 6
//Country 2,Latitude 2,Longitude 2,Location Id 2,                                             // 4
//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,         // 6
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                             // 4
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,         // 6
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                             // 4
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,         // 6
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                             // 4
//Extension Phone 1,Extension 1,Extension Phone Country 1,                                    // 3
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                    // 3
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                    // 3
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                    // 3
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                    // 3
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                    // 6
//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                    // 6
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,            // 5
//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                  // 2
//Plain Text Email - 2 way,                                                                   // 1
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                                // 6
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                    // 4
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                                // 6
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                                // 6
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                // 4
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                  // 3
//One Way SMS,One Way SMS Country,                                                            // 2
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3,  // 6
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6,  // 6
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9,END//6
*/



void EverBridgeRpt::operator() () {
MbrListIter iter(memberList);
MbrInfo*    item;
int         count;

  header();

  for (count = 0, item = iter(); item; item = iter++) if (item->curMbr) {output(*item);   count++;}

  msgCount(count);
  }


void EverBridgeRpt::header() {
  csv << _T("First Name")                       << Comma;
  csv << _T("Middle Initial")                   << Comma;
  csv << _T("Last Name")                        << Comma;
  csv << _T("Suffix")                           << Comma;
  csv << _T("External ID")                      << Comma;
  csv << _T("Country")                          << Comma;
  csv << _T("Business Name")                    << Comma;
  csv << _T("Record Type")                      << Comma;
  csv << _T("Groups")                           << Comma;
  csv << _T("SSO User ID")                      << Comma;
  csv << _T("Travel Arranger")                  << Comma;
  csv << _T("Location 1")                       << Comma;
  csv << _T("Street Address 1")                 << Comma;
  csv << _T("Apt/Suite/Unit 1")                 << Comma;
  csv << _T("City 1")                           << Comma;
  csv << _T("State/Province 1")                 << Comma;
  csv << _T("Postal Code 1")                    << Comma;
  csv << _T("Country 1")                        << Comma;
  csv << _T("Latitude 1")                       << Comma;
  csv << _T("Longitude 1")                      << Comma;
  csv << _T("Location Id 1")                    << Comma;
  csv << _T("Location 2")                       << Comma;
  csv << _T("Street Address 2")                 << Comma;
  csv << _T("Apt/Suite/Unit 2")                 << Comma;
  csv << _T("City 2")                           << Comma;
  csv << _T("State/Province 2")                 << Comma;
  csv << _T("Postal Code 2")                    << Comma;
  csv << _T("Country 2")                        << Comma;
  csv << _T("Latitude 2")                       << Comma;
  csv << _T("Longitude 2")                      << Comma;
  csv << _T("Location Id 2")                    << Comma;
  csv << _T("Location 3")                       << Comma;
  csv << _T("Street Address 3")                 << Comma;
  csv << _T("Apt/Suite/Unit 3")                 << Comma;
  csv << _T("City 3")                           << Comma;
  csv << _T("State/Province 3")                 << Comma;
  csv << _T("Postal Code 3")                    << Comma;
  csv << _T("Country 3")                        << Comma;
  csv << _T("Latitude 3")                       << Comma;
  csv << _T("Longitude 3")                      << Comma;
  csv << _T("Location Id 3")                    << Comma;
  csv << _T("Location 4")                       << Comma;
  csv << _T("Street Address 4")                 << Comma;
  csv << _T("Apt/Suite/Unit 4")                 << Comma;
  csv << _T("City 4")                           << Comma;
  csv << _T("State/Province 4")                 << Comma;
  csv << _T("Postal Code 4")                    << Comma;
  csv << _T("Country 4")                        << Comma;
  csv << _T("Latitude 4")                       << Comma;
  csv << _T("Longitude 4")                      << Comma;
  csv << _T("Location Id 4")                    << Comma;
  csv << _T("Location 5")                       << Comma;
  csv << _T("Street Address 5")                 << Comma;
  csv << _T("Apt/Suite/Unit 5")                 << Comma;
  csv << _T("City 5")                           << Comma;
  csv << _T("State/Province 5")                 << Comma;
  csv << _T("Postal Code 5")                    << Comma;
  csv << _T("Country 5")                        << Comma;
  csv << _T("Latitude 5")                       << Comma;
  csv << _T("Longitude 5")                      << Comma;
  csv << _T("Location Id 5")                    << Comma;
  csv << _T("Extension Phone 1")                << Comma;
  csv << _T("Extension 1")                      << Comma;
  csv << _T("Extension Phone Country 1")        << Comma;
  csv << _T("Extension Phone 2")                << Comma;
  csv << _T("Extension 2")                      << Comma;
  csv << _T("Extension Phone Country 2")        << Comma;
  csv << _T("Extension Phone 3")                << Comma;
  csv << _T("Extension 3")                      << Comma;
  csv << _T("Extension Phone Country 3")        << Comma;
  csv << _T("Extension Phone 4")                << Comma;
  csv << _T("Extension 4")                      << Comma;
  csv << _T("Extension Phone Country 4")        << Comma;
  csv << _T("Extension Phone 5")                << Comma;
  csv << _T("Extension 5")                      << Comma;
  csv << _T("Extension Phone Country 5")        << Comma;
  csv << _T("Phone 1")                          << Comma;
  csv << _T("Phone Country 1")                  << Comma;
  csv << _T("Phone 2")                          << Comma;
  csv << _T("Phone Country 2")                  << Comma;
  csv << _T("Phone 3")                          << Comma;
  csv << _T("Phone Country 3")                  << Comma;
  csv << _T("Phone 4")                          << Comma;
  csv << _T("Phone Country 4")                  << Comma;
  csv << _T("Phone 5")                          << Comma;
  csv << _T("Phone Country 5")                  << Comma;
  csv << _T("Phone 6")                          << Comma;
  csv << _T("Phone Country 6")                  << Comma;
  csv << _T("Email Address 1")                  << Comma;
  csv << _T("Email Address 2")                  << Comma;
  csv << _T("Email Address 3")                  << Comma;
  csv << _T("Email Address 4")                  << Comma;
  csv << _T("Email Address 5")                  << Comma;
  csv << _T("Plain Text Email - 1 way")         << Comma;
  csv << _T("Plain Text - 1 way Pager Service") << Comma;
  csv << _T("Plain Text Email - 2 way")         << Comma;
  csv << _T("SMS 1")                            << Comma;
  csv << _T("SMS 1 Country")                    << Comma;
  csv << _T("SMS 2")                            << Comma;
  csv << _T("SMS 2 Country")                    << Comma;
  csv << _T("SMS 3")                            << Comma;
  csv << _T("SMS 3 Country")                    << Comma;
  csv << _T("SMS 4")                            << Comma;
  csv << _T("SMS 4 Country")                    << Comma;
  csv << _T("SMS 5")                            << Comma;
  csv << _T("SMS 5 Country")                    << Comma;
  csv << _T("FAX 1")                            << Comma;
  csv << _T("FAX Country 1")                    << Comma;
  csv << _T("FAX 2")                            << Comma;
  csv << _T("FAX Country 2")                    << Comma;
  csv << _T("FAX 3")                            << Comma;
  csv << _T("FAX Country 3")                    << Comma;
  csv << _T("TTY 1")                            << Comma;
  csv << _T("TTY Country 1")                    << Comma;
  csv << _T("TTY 2")                            << Comma;
  csv << _T("TTY Country 2")                    << Comma;
  csv << _T("TTY 3")                            << Comma;
  csv << _T("TTY Country 3")                    << Comma;
  csv << _T("Numeric Pager")                    << Comma;
  csv << _T("Numeric Pager Country")            << Comma;
  csv << _T("Numeric Pager Pin")                << Comma;
  csv << _T("Numeric Pager Service")            << Comma;
  csv << _T("TAP Pager")                        << Comma;
  csv << _T("TAP Pager Country")                << Comma;
  csv << _T("TAP Pager Pin")                    << Comma;
  csv << _T("One Way SMS")                      << Comma;
  csv << _T("One Way SMS Country")              << Comma;
  csv << _T("Custom Field 1")                   << Comma;
  csv << _T("Custom Value 1")                   << Comma;
  csv << _T("Custom Field 2")                   << Comma;
  csv << _T("Custom Value 2")                   << Comma;
  csv << _T("Custom Field 3")                   << Comma;
  csv << _T("Custom Value 3")                   << Comma;
  csv << _T("Custom Field 4")                   << Comma;
  csv << _T("Custom Value 4")                   << Comma;
  csv << _T("Custom Field 5")                   << Comma;
  csv << _T("Custom Value 5")                   << Comma;
  csv << _T("Custom Field 6")                   << Comma;
  csv << _T("Custom Value 6")                   << Comma;
  csv << _T("Custom Field 7")                   << Comma;
  csv << _T("Custom Value 7")                   << Comma;
  csv << _T("Custom Field 8")                   << Comma;
  csv << _T("Custom Value 8")                   << Comma;
  csv << _T("Custom Field 9")                   << Comma;
  csv << _T("Custom Value 9")                   << Comma;
  csv << _T("Custom Field 10")                  << Comma;
  csv << _T("Custom Value 10")                  << Comma;
  csv << _T("Custom Field 11")                  << Comma;
  csv << _T("Custom Value 11")                  << Comma;
  csv << _T("Custom Field 12")                  << Comma;
  csv << _T("Custom Value 12")                  << Comma;
  csv << _T("Custom Field 13")                  << Comma;
  csv << _T("Custom Value 13")                  << Comma;
  csv << _T("Custom Field 14")                  << Comma;
  csv << _T("Custom Value 14")                  << Comma;
  csv << _T("END") << Comma;
  csv << vCrlf;
  }



/*
//First Name,Middle Initial,Last Name,Suffix,External ID,                                     // 5
Craig,,Anderson,,RACES-N6YXK,

//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                          // 6
US,,RACES,SJS RACES|SJS RACES 5 No Dispatch,,,

//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,         // 6
Home,14656 Bronson Avenue,,San Jose,CA,95124,

//Country 1,Latitude 1,Longitude 1,Location Id 1,                                             // 4
US,37.25438,-121.92522,,

//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,         // 6
,,,,,,
//Country 2,Latitude 2,Longitude 2,Location Id 2,                                             // 4
,,,,
//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,         // 6
,,,,,,
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                             // 4
,,,,
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,         // 6
,,,,,,
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                             // 4
,,,,
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,         // 6
,,,,,,
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                             // 4
,,,,

//Extension Phone 1,Extension 1,Extension Phone Country 1,                                    // 3
,,,
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                    // 3
,,,
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                    // 3
,,,
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                    // 3
,,,
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                    // 3
,,,
      Cell                       Work?                       Home
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                    // 6
4087686025,US,,,4083718904,US,

//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                    // 6
,,,,,,
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,            // 5
,acraiga@pacbell.net,,,,

//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                  // 2
,,
//Plain Text Email - 2 way,                                                                   // 1
,
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                                // 6
4087686025,US,,,,,
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                    // 4
,,,,
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                                // 6
,,,,,,
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                                // 6
,,,,,,
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                // 4
,,,,
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                  // 3
,,,
//One Way SMS,One Way SMS Country,                                                            // 2
,,
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3,  // 6
,Certifications,RACES,,,,
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6,  // 6
,,,,,,
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9,END//6
,,,,,,
,,,,,,,,,,END
*/

/*


Scott,L,Bordelon,,RACES-K6SLB,US,,RACES,SJS RACES|SJS RACES 1 Priority|SJS RACES 0 Officers,,,
Home,5659 Algonquin Way,,San Jose,CA,951382245,US,37.27084,-121.7694,,
Work,150 Rose Orchard Way,,San Jose,CA,95134,US,37.41737,-121.94735,,
,,,,,,,,,,END


//First Name,Middle Initial,Last Name,Suffix,External ID,                                    // 5
//Scott,L,Bordelon,,RACES-K6SLB

//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                         // 6
//US,,RACES,SJS RACES|SJS RACES 1 Priority|SJS RACES 0 Officers,,,

//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,        // 6
Home,5659 Algonquin Way,,San Jose,CA,951382245,

//Country 1,Latitude 1,Longitude 1,Location Id 1,                                            // 4
US,37.27084,-121.7694,,

//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,        // 6
Work,150 Rose Orchard Way,,San Jose,CA,95134

//Country 2,Latitude 2,Longitude 2,Location Id 2,                                            // 4
US,37.41737,-121.94735,,

//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,        // 6
,,,,,,
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                            // 4
,,,,
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,        // 6
,,,,,,
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                            // 4
,,,,
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,        // 6
,,,,,,
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                            // 4
,,,,
//Extension Phone 1,Extension 1,Extension Phone Country 1,                                   // 3
,,,
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                   // 3
,,,
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                   // 3
,,,
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                   // 3
,,,
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                   // 3
,,,
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                   // 6
4084311862,US,4085761341,US,4082700422,US,
//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                   // 6
,,,,,,
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,           // 5
scott.bordelon@intel.com,scott.bordelon@gmail.com,,,,
//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                 // 2
,,
//Plain Text Email - 2 way,                                                                  // 1
,
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                               // 6
4084311862,US,,,,,
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                   // 4
,,,,
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                               // 6
,,,,,,
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                               // 6
,,,,,,
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,               // 4
,,,,
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                 // 3
,,,
//One Way SMS,One Way SMS Country,                                                           // 2
,,
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3, // 6
Certifications,RACES,,,,,
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6, // 6
,,,,,,
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9, // 6
,,,,,,
//END
*/


void EverBridgeRpt::output(MbrInfo& info) {
MbrRcd& rcd       = *info.mbrRcd;
EntRcd* mbrEnt    =  info.mbrEnt;
EntRcd* emplRcd   =  info.emplEnt;
AsnRcd* asnRcd    =  info.asnRcd;
LocRcd* locRcd    =  info.locRcd;
StsRcd* stsRcd    =  info.stsRcd;
String  responder =  rcd.responder.trim();
String  dsw       =  rcd.dSWDate.trim();
String  key;
String  s;

  csv << mbrEnt->firstName << Comma;                      // First Name
  csv << mbrEnt->middleInitial << Comma;                  // Middle Initial
  csv << mbrEnt->lastName << Comma;                       // Last Name
  csv << mbrEnt->suffix << Comma;                         // Suffix

  s = _T("RACES-") + rcd.callSign;  csv << s << Comma;    // External ID

  s = _T("US"); csv << s << Comma;                        // Country

  csv << Comma;                                           // Business Name

  s = _T("RACES"); csv << s << Comma;                     // Record Type

  s = _T("SJS RACES");

  if (asnRcd) {
    key = asnRcd->aPKey;
    if      (key == _T("P")) s += _T("|SJS RACES 1 Priority");
    else if (key == _T("E")) s += _T("|SJS RACES 2 Emergency");
    else if (key == _T("G")) s += _T("|SJS RACES 3 General");
    else if (key == _T("L")) s += _T("|SJS RACES 4 Last Resort");
    else if (key == _T("A")) s += _T("|SJS RACES 5 No Dispatch");
    else if (key == _T("N")) s += _T("|SJS RACES 6 Non-Responder");
    else                     s += _T("|SJS RACES 7 Other");
    }

  if (rcd.isOfficer) s += _T("|SJS RACES 0 Officers");
  csv << s << Comma;                                        // Groups

  csv << nCommas(2);                                        // SSO User ID,Group Remove,

  s.clear();

  location(_T("Home"), mbrEnt);                             // Location 1
  location(_T("Work"), emplRcd);                            // Location 2
  location(0, 0);                                           // Location 3
  location(0, 0);                                           // Location 4
  location(0, 0);                                           // Location 5

  csv << nCommas(3);                                        // Extension Phone 1
  csv << nCommas(3);                                        // Extension Phone 2
  csv << nCommas(3);                                        // Extension Phone 3
  csv << nCommas(3);                                        // Extension Phone 4
  csv << nCommas(3);                                        // Extension Phone 5

  String empty;

  phone(mbrEnt  ? mbrEnt->phone2  : empty);                     //Phone 1
  phone(emplRcd ? emplRcd->phone2 : empty);                     //Phone 2
  phone(mbrEnt  ? mbrEnt->phone1  : empty);                     //Phone 3
  phone(emplRcd ? emplRcd->phone1 : empty);                     //Phone 4
  phone(0);                                                 //Phone 5
  phone(0);                                                 //Phone 6

  eMail(mbrEnt  ?  mbrEnt->eMail : empty);                      // Email Address 1
  eMail(emplRcd ? emplRcd->eMail : empty);                      // Email Address 2
  csv << Comma;                                             // Email Address 3
  csv << Comma;                                             // Email Address 4
  csv << Comma;                                             // Email Address 5

  csv << Comma;                                             // Plain Text Email - 1 way
  csv << Comma;                                             // Plain Text - 1 way Pager Service

  csv << Comma;                                             // Plain Text Email - 2 way

  phone(rcd.textMsgPh1);                                    // SMS 1
  phone(rcd.textMsgPh2);                                    // SMS 2
  csv << nCommas(2);                                        // SMS 3
  csv << nCommas(2);                                        // SMS 4
  csv << nCommas(2);                                        // SMS 5

  csv << nCommas(2);                                        // FAX 1
  csv << nCommas(2);                                        // FAX 2
  csv << nCommas(2);                                        // FAX 3

  csv << nCommas(2);                                        // TTY 1
  csv << nCommas(2);                                        // TTY 2
  csv << nCommas(2);                                        // TTY 3

  //Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,              // 4
  csv << nCommas(4);

  //TAP Pager,TAP Pager Country,TAP Pager Pin,                                                // 3
  csv << nCommas(3);

  phone(0);                                                       // One Way SMS

  csv << _T("Certifications") << Comma;                                      // Custom Field 1
  csv << _T("RACES") << Comma;                                               // Custom Field 2
  csv << nCommas(26);
  csv << _T("END") << vCrlf;
  }


void EverBridgeRpt::location(TCchar* title, EntRcd* rcd) {
AdrRcd* addrRcd = 0;
CtyRcd* cityRcd = 0;
String  s;

  if (rcd) {
    addrRcd = adrTbl.find(rcd->addrID);
    cityRcd = ctyTbl.find(rcd->cityStID);
    }

  if (!rcd || !addrRcd || (addrRcd->address1.isEmpty() && !rcd->addrIsPO)) {
    //Location n,Street Address n,Apt/Suite/Unit n,City n,State/Province n,Postal Code n,     // 6
    csv << nCommas(6);
    //Country n,Latitude n,Longitude n,Location Id n,                                         // 4
    csv << nCommas(4);   return;
    }

  csv << title << Comma;                                                      // Location n

  if (rcd->addrIsPO) {                                                        // Street Address n
    s = !addrRcd->address1.isEmpty() ? addrRcd->address1 : String(_T("PO Box 1234"));
    csv << s << Comma << Comma;                                               // Apt/Suite/Unit n

    if (cityRcd) {
      s = !cityRcd->city.isEmpty()   ? cityRcd->city     : String(_T("San Jose"));
      csv << s << Comma;
                                                                              // City n
      s = !cityRcd->state.isEmpty()  ? cityRcd->state    : String(_T("CA"));
      csv << s << Comma;
                                                                              // State/Province
      csv << expandZip(cityRcd->zip) << Comma;                                           // Postal Code 1
      }
    else {
      csv << _T("San Jose")   << Comma;                                       // City n
      csv << _T(" CA")        << Comma;                                       // State/Province n
      csv << rcd->locationZip << Comma;                                       // Postal Code 1
      }
    }

  else {
    csv << addrRcd->address1 << Comma;                                       // Street Address n
    csv << addrRcd->address2 << Comma;                                       // Apt/Suite/Unit n

    if (cityRcd) {
      s = !cityRcd->city.isEmpty()  ? cityRcd->city  : String(_T("San Jose"));
      csv << s << Comma;                                                      // City n
      s = !cityRcd->state.isEmpty() ? cityRcd->state : String(_T(" CA"));
      csv << s << Comma;                                                      // State/Province
      csv << expandZip(cityRcd->zip) << Comma;                                           // Postal Code n
      }
    else {
      s = _T("San Jose"); csv << s << Comma;                                  // City n
      s = _T(" CA");      csv << s << Comma;                                  // State/Province n
      csv << Comma;                                                           // Postal Code n
      }
    }

  //Country 1,Latitude 1,Longitude 1,Location Id 1,                           // 4

  s = _T("US"); csv << s << Comma;   csv << nCommas(3);
  }



//Phone 1,Phone Country 1,

void EverBridgeRpt::phone(TCchar* ph) {
String s = expandPhone(ph);

  if (s.empty()) {csv << nCommas(2); return;}

  csv << s << Comma << _T("US") << Comma;                              // Phone n & Phone Country n
  }



void EverBridgeRpt::eMail(TCchar* em)
                                   {String s = em;    s.trim();   csv << s << Comma;}

