// Races App Reports


#pragma once

class PathDlgDsc;


class Reports {

String reportPath;

public:

          Reports() { }
         ~Reports() { }

  void    excelRpt();
  void    googleRpt();
  void    everBridgeRpt();
  void    csBadgeRpt();
  void    dateBadgeRpt();
  void    contactNm();
  void    contactCS();
  void    responderCnts();
  void    callSignList();
  void    memberIDs();

private:

  String& getPathDsc(TCchar* fileName);
  TCchar* getOutputPath(PathDlgDsc& dsc);
  };

