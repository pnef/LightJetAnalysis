# --------------------------------------------- #
# Makefile for LightJetAnalysis code            #
# Pascal Nef, June 4th 2014                    #
#                                               #
# Note: source setup.sh before make             #
# --------------------------------------------- #

CXXFLAGS =   -O2 -Wall 

.PHONY: clean debug all



all: test runLightJetAnalysis

# ------ check if boost is installed --------
test:
ifeq ($(BOOSTSETUP), 1)
boostincl := -L$(BOOSTLIBLOCATION)
boostlib := -lboost_program_options
CXXFLAGS += -Dboostflag=1
else
boostlib := 
boostlib :=
CXXFLAGS += -Dboostflag=0
endif	
# -------------

runLightJetAnalysis:  runLightJetAnalysis.so 
	$(CXX) runLightJetAnalysis.so LightJetAnalysis.so LightJetAnalysisBase.so -o $@.exe \
	$(CXXFLAGS) -Wno-shadow  \
	`root-config --glibs`  \
	-L$(FASTJETLOCATION)/lib `$(FASTJETLOCATION)/bin/fastjet-config --libs --plugins `  \
	$(boostincl) $(boostlib)


LightJetAnalysisBase.so:   LightJetAnalysisBase.C   LightJetAnalysisBase.h 
	$(CXX) -o $@ -c $<  \
	$(CXXFLAGS) -Wno-shadow -fPIC -shared \
	`$(FASTJETLOCATION)/bin/fastjet-config --cxxflags --plugins`  \
	`root-config --cflags` 

LightJetAnalysis.so: LightJetAnalysis.cc    LightJetAnalysis.h  LightJetAnalysisBase.so 
	$(CXX) -o $@ -c $<  \
	$(CXXFLAGS) -Wno-shadow -fPIC -shared \
	`$(FASTJETLOCATION)/bin/fastjet-config --cxxflags --plugins`  \
	`root-config --cflags` 

runLightJetAnalysis.so: runLightJetAnalysis.C LightJetAnalysis.so LightJetAnalysisBase.so 
	$(CXX) -o $@ -c $<  \
	$(CXXFLAGS) -Wno-shadow -fPIC -shared \
	`$(FASTJETLOCATION)/bin/fastjet-config --cxxflags --plugins`  \
	`root-config --cflags` \
	$(boostincl) 

clean:
	rm -rf *.exe
	rm -rf *.o
	rm -rf *.so
	rm -f *~



