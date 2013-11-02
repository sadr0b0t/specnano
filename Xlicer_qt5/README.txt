Для того, чтобы запустить проект, необходимо скачать библиотеку qt версии 5.1.1 с оф. сайта:
http://qt-project.org/downloads
Далее после установки библиотеки вместе с IDE Qtcreator, открываем Qt Project file "Xlicer_qt5".
После построения бинарного файла проекта, в дирректорию, где у Вас находится бинарный файл Xlicer_qt5.exe
скопируйте следующие файлы:
для программы в папке release:
	Qt5Core.dll
	Qt5Gui.dll
	Qt5OpenGL.dll
	Qt5Widgets.dll
	libgcc_s_dw2-1.dll
	libstdc++-6.dll
	icudt51.dll
	icuin51.dll
	icuuc51.dll
	libwinpthread-1.dll

для программы в папке debug:
	Qt5Cored.dll
	Qt5Guid.dll
	Qt5OpenGLd.dll
	Qt5Widgetsd.dll
	libgcc_s_dw2-1.dll
	libstdc++-6.dll
	icudt51.dll
	icuin51.dll
	icuuc51.dll
	libwinpthread-1.dll

находящиеся в папке: \путь к установленной библиотеки Qt5.1.1\Qt5.1.1\5.1.1\mingw48_32\bin
например: C:\Qt\Qt5.1.1\5.1.1\mingw48_32\bin
Затем запускаете файл Xlicer_qt5.exe и работаете с приложением.