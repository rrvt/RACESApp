

RacesApp.chm : *.htm RacesApp.hhp RacesApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RacesApp.chm del /f RacesApp.chm


$(TgtFolder)/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\$(TgtFolder)\RacesApp.chm


$(TgtFolder)/Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/RacesApp.chm



