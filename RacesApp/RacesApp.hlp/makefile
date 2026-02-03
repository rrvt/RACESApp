

RacesApp.chm : *.htm RacesApp.hhp RacesApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RacesApp.chm del /f RacesApp.chm


Release.x64/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Release.x64\RacesApp.chm


Release.x64/Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Release.x64
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Debug.x64/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Debug.x64\RacesApp.chm


Debug.x64\Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Debug.x64
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Release.x64/Rebuild.rbd : Release.x64/Clean.cln Release.x64/RacesApp.chm


Debug.x64/Rebuild.rbd   : Debug.x64/Clean.cln Debug.x64/RacesApp.chm


Release.Win32/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Release.Win32\RacesApp.chm


Release.Win32/Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Release.Win32
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Debug.Win32/RacesApp.chm : RacesApp.chm
  copy $(MAKEDIR)\RacesApp.chm  $(MAKEDIR)\..\Debug.Win32\RacesApp.chm


Debug.Win32\Clean.cln : Clean.cln
  cd $(MAKEDIR)\..\Debug.Win32
  if exist RacesApp.chm del /f RacesApp.chm
  cd $(MAKEDIR)


Release.Win32/Rebuild.rbd : Release.Win32/Clean.cln Release.Win32/RacesApp.chm


Debug.Win32/Rebuild.rbd   : Debug.Win32/Clean.cln Debug.Win32/RacesApp.chm


