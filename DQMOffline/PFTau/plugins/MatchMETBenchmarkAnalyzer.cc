#include "DQMOffline/PFTau/plugins/MatchMETBenchmarkAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/METReco/interface/MET.h"

using namespace reco;
using namespace edm;
using namespace std;

MatchMETBenchmarkAnalyzer::MatchMETBenchmarkAnalyzer(const edm::ParameterSet& parameterSet) : 
  BenchmarkAnalyzer(parameterSet),
  MatchMETBenchmark( (Benchmark::Mode) parameterSet.getParameter<int>("mode") )
{
  matchedInputLabel_=parameterSet.getParameter<edm::InputTag>("MatchCollection");
//  setRange( parameterSet.getParameter<double>("ptMin"),
//	    parameterSet.getParameter<double>("ptMax"),
//	    -0.1, 0.1, // range in eta for MET. 
//	    parameterSet.getParameter<double>("phiMin"),
//	    parameterSet.getParameter<double>("phiMax") );
}

void 
MatchMETBenchmarkAnalyzer::beginJob()
{

  BenchmarkAnalyzer::beginJob();
  setup();
}

void 
MatchMETBenchmarkAnalyzer::analyze(const edm::Event& iEvent, 
				      const edm::EventSetup& iSetup) {
  
  
  Handle< View<MET> > collection; 
  //iEvent.getByLabel( inputLabel_, collection); 
  EDGetTokenT< View<MET> > myColl_;
  myColl_ = consumes< View<MET> >(inputLabel_);
  iEvent.getByToken(myColl_, collection);

  Handle< View<MET> > matchedCollection; 
  //iEvent.getByLabel( matchedInputLabel_, matchedCollection); 
  myMatchColl_ = consumes< View<MET> >(matchedInputLabel_);
  iEvent.getByToken(myMatchColl_, matchedCollection);

  fillOne( (*collection)[0] , (*matchedCollection)[0]);
}

void MatchMETBenchmarkAnalyzer::endJob() {
}
