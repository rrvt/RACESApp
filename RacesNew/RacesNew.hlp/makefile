

RacesNew.chm : *.htm RacesNew.hhp RacesNew.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesNew


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F RacesNew.chm


Release/RacesNew.chm : RacesNew.chm
  copy $(MAKEDIR)\RacesNew.chm  $(MAKEDIR)\..\Release\RacesNew.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del RacesNew.chm
  cd $(MAKEDIR)


Debug/RacesNew.chm : RacesNew.chm
  copy $(MAKEDIR)\RacesNew.chm  $(MAKEDIR)\..\Debug\RacesNew.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del RacesNew.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RacesNew.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RacesNew.chm


