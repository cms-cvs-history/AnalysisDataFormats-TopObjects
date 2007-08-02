#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"
#include "AnalysisDataFormats/TopObjects/interface/StGenEvent.h"

#include "AnalysisDataFormats/TopObjects/test/testGenEvent.h"

using namespace edm;
using namespace std;
//using namespace reco;

testGenEvent::testGenEvent(const edm::ParameterSet& pset)
{
  process = pset.getParameter<std::string>("proc");
}

testGenEvent::~testGenEvent()
{

}

void testGenEvent::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nevt++;
  cout <<"----------------------------"<<endl;
  cout << "(testGenEvent) Event n." << nevt << endl;
  using namespace edm;

  if (process == "tt") {
    Handle<TtGenEvent> ttevent;
    iEvent.getByLabel("genEvt", ttevent);

    if ( ttevent->isFullHadronic() ) {
      cout << " is fully hadronic" << endl;
    } else if ( ttevent->isSemiLeptonic() ) {
      cout << " is semileptonic" << endl;

      cout << " # leptons: " << ttevent->numberOfLeptons() << ", # b-quarks: " << ttevent->numberOfBQuarks() << endl;
      const reco::Candidate* cand = ttevent->singleLepton();
      if (cand) {
	cout << " lepton pt: " << cand->p() << endl;
      } else {
	cout << "  there is a problem" << endl;
      }


    } else if ( ttevent->isFullLeptonic() ) {
      cout << " is fully leptonic" << endl;
    }

    // insert here whatever you think can be interesting for ttbar events...

  } else if (process == "st") {
    Handle<StGenEvent> stevent;
    iEvent.getByLabel("genEvtSingletop", stevent);

    cout << " # leptons: " << stevent->numberOfLeptons() << ", # b-quarks: " << stevent->numberOfBQuarks() << ", # light quarks: " << stevent->lightQuarks(false).size() << endl;
    const reco::Candidate* l = stevent->singleLepton();
    const reco::Candidate* b = stevent->decayB();
    const reco::Candidate* ab = stevent->associatedB();
    const reco::Candidate* w = stevent->singleW();
    const reco::Candidate* t = stevent->singleTop();
    if (l) cout << " lepton pt: " << l->pt() << endl;
    if (b) cout << " b(<-t) pt: " << b->pt() << endl;
    if (ab) cout << " b(ass.) pt: " << ab->pt() << endl;
    if (w) cout << " W pt: " << w->pt() << endl;
    if (t) cout << " t pt: " << t->pt() << endl;
    if (t && w && b) {
      cout << "Consistency check: does the vectorial sum of W and b give the t?" << endl;
      cout << " t: px = " << t->px() << ", py = " << t->py() << ", pz = " << t->pz() << endl;
      cout << " W+b: px = " << w->px()+b->px() << ", py = " << w->py()+b->py() << ", pz = " << w->pz()+b->pz() << endl;
    }
    //    } else {
    //      cout << "  there is a problem" << endl;
    //    }

  } else {
    cout << "(testGenEvent) unrecognized label: " << process << endl;
  }

}


void testGenEvent::beginJob(const edm::EventSetup&){
  nevt=0;

}

void testGenEvent::endJob() {

  cout << "(testGenEvent) Processed " << nevt << " events." << endl;

  return ;
}

DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE(testGenEvent);
