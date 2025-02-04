

RacesApp.chm : *.htm RacesApp.hhp RacesApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RacesApp.chm del /f RacesApp.chm


Release/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Release\RacesApp.chm


Release/Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Debug/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Debug\RacesApp.chm


Debug\Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RacesApp.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RacesApp.chm


