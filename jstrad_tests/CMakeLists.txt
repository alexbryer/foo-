
add_executable(compare compare.cpp)
INSTALL(TARGETS compare DESTINATION bin)

if(WIN32)
  set(EXE_NAME qinstrument.exe)
  set(COMPARE_EXE_NAME compare.exe)
else()
  set(EXE_NAME qinstrument)
  set(COMPARE_EXE_NAME compare)
endif()

# these tests should pass

#TEST 00
add_test(NAME jstrad_test00
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test00_No_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test00.wav
    )
	add_test(NAME jstrad_test00_harmonic1
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test00_Harmonic1-0.wav ${CMAKE_SOURCE_DIR}/tests/test00_harmonic1.wav
    )
	add_test(NAME jstrad_test00_harmonic2
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test00_Harmonic2-0.wav ${CMAKE_SOURCE_DIR}/tests/test00_harmonic2.wav
    )
	add_test(NAME jstrad_test00_harmonicboth
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test00_Both_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test00_harmonicboth.wav
    )
#TEST 01
add_test(NAME jstrad_test01
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test01_No_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test01.wav
    )
	add_test(NAME jstrad_test01_harmonic1
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test01_Harmonic1-0.wav ${CMAKE_SOURCE_DIR}/tests/test01_harmonic1.wav
    )
	add_test(NAME jstrad_test01_harmonic2
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test01_Harmonic2-0.wav ${CMAKE_SOURCE_DIR}/tests/test01_harmonic2.wav
    )
	add_test(NAME jstrad_test01_harmonicboth
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test01_Both_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test01_harmonicboth.wav
    )
#TEST 02
add_test(NAME jstrad_test02
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test02_No_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test02.wav
    )
	add_test(NAME jstrad_test02_harmonic1
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test02_Harmonic1-0.wav ${CMAKE_SOURCE_DIR}/tests/test02_harmonic1.wav
    )
	add_test(NAME jstrad_test02_harmonic2
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test02_Harmonic2-0.wav ${CMAKE_SOURCE_DIR}/tests/test02_harmonic2.wav
    )
	add_test(NAME jstrad_test02_harmonicboth
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test02_Both_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test02_harmonicboth.wav
    )
#TEST 03
add_test(NAME jstrad_test03
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test03_No_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test03.wav
    )
	add_test(NAME jstrad_test03_harmonic1
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test03_Harmonic1-0.wav ${CMAKE_SOURCE_DIR}/tests/test03_harmonic1.wav
    )
	add_test(NAME jstrad_test03_harmonic2
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test03_Harmonic2-0.wav ${CMAKE_SOURCE_DIR}/tests/test03_harmonic2.wav
    )
	add_test(NAME jstrad_test03_harmonicboth
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test03_Both_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test03_harmonicboth.wav
    )
#TEST 04
add_test(NAME jstrad_test04
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_No_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test04.wav
    )
	add_test(NAME jstrad_test04_harmonic1
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_Harmonic1-0.wav ${CMAKE_SOURCE_DIR}/tests/test04_harmonic1.wav
    )
	add_test(NAME jstrad_test04_harmonic2
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_Harmonic2-0.wav ${CMAKE_SOURCE_DIR}/tests/test04_harmonic2.wav
    )
	add_test(NAME jstrad_test04_harmonicboth
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_Both_Harmonics-0.wav ${CMAKE_SOURCE_DIR}/tests/test04_harmonicboth.wav
    )
	#added
	add_test(NAME jstrad_test04_longer
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_Both_Harmonics_Longer-0.wav ${CMAKE_SOURCE_DIR}/tests/test04_longer.wav
    )
	add_test(NAME jstrad_test04_velocity
  COMMAND ${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME} ${CMAKE_SOURCE_DIR}/QTest_Test04_Both_Harmonics_Velocity-0.wav ${CMAKE_SOURCE_DIR}/tests/test04_velocity.wav
    )
	
	
	
	
	
	
	
	
	
	

