#ifndef TopObjects_TtSemiEvent_h
#define TopObjects_TtSemiEvent_h

#include <vector>
#include <string>

#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/RefProd.h"

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

#include "DataFormats/Candidate/interface/CandidateWithRef.h"
#include "DataFormats/Candidate/interface/NamedCompositeCandidate.h"

namespace TtSemiDaughter{
  // semileptonic daughter names
  static const std::string Nu  ="Nu",   Lep ="Lep",  LepW="LepW", LepB="LepB", LepTop="LepTop";
  static const std::string HadQ="HadQ", HadP="HadP", HadW="HadW", HadB="HadB", HadTop="HadTop"; 
}

class TtSemiEvent {
  
 public:

  // semiletponic decay channels
  enum Decay {kNone, kElec, kMuon, kTau};

  // supported EventHypotheses
  enum HypoKey {kGeom, kWMassMaxSumPt, kMaxSumPtWMass, kGenMatch, kMVADisc, kKinFit};

  // typdefs for hierarchical EventHypothesis
  typedef reco::CandidateWithRef<edm::Ref<std::vector<pat::Jet> > > JetCandRef;
  typedef reco::CandidateWithRef<edm::Ref<std::vector<pat::Electron> > > ElectronCandRef;
  typedef reco::CandidateWithRef<edm::Ref<std::vector<pat::Muon> > > MuonCandRef;
  typedef reco::CandidateWithRef<edm::Ref<std::vector<pat::MET> > > METCandRef;
  
 public:

  TtSemiEvent();
  virtual ~TtSemiEvent(){};

  // access decay 
  Decay decay() const { return decay_;}

  // access objects according to corresponding EventHypothesis
  const reco::NamedCompositeCandidate& eventHypo(const HypoKey& key) const { return evtHyp_.find(key)->second; };
  // warning: since access by string to the daughters of a daughter is not yet possible, for the time being
  //          daughters have to be added always in the same order to their mothers before adding these to
  //          the event hypothesis in order to have the correct objects returned by the following functions
  // (for top quarks: first W, then b quark; for the hadr. decaying W: first quark, then anti-quark;
  //                                         for the lept. decaying W: first lepton, then neutrino)
  const reco::Candidate* hadronicTop(const HypoKey& key) const { return !isHypoValid(key) ? 0 : eventHypo(key).   daughter(TtSemiDaughter::HadTop); };
  const reco::Candidate* hadronicB  (const HypoKey& key) const { return !isHypoValid(key) ? 0 : hadronicTop(key)->daughter(1);                      };
  const reco::Candidate* hadronicW  (const HypoKey& key) const { return !isHypoValid(key) ? 0 : hadronicTop(key)->daughter(0);                      };
  const reco::Candidate* lightQuarkP(const HypoKey& key) const { return !isHypoValid(key) ? 0 : hadronicW(key)->  daughter(1);                      };
  const reco::Candidate* lightQuarkQ(const HypoKey& key) const { return !isHypoValid(key) ? 0 : hadronicW(key)->  daughter(0);                      };
  const reco::Candidate* leptonicTop(const HypoKey& key) const { return !isHypoValid(key) ? 0 : eventHypo(key).   daughter(TtSemiDaughter::LepTop); };
  const reco::Candidate* leptonicB  (const HypoKey& key) const { return !isHypoValid(key) ? 0 : leptonicTop(key)->daughter(1);                      };
  const reco::Candidate* leptonicW  (const HypoKey& key) const { return !isHypoValid(key) ? 0 : leptonicTop(key)->daughter(0);                      };
  const reco::Candidate* neutrino   (const HypoKey& key) const { return !isHypoValid(key) ? 0 : leptonicW(key)->  daughter(1);                      };
  const reco::Candidate* lepton     (const HypoKey& key) const { return !isHypoValid(key) ? 0 : leptonicW(key)->  daughter(0);                      };

  // access the matched gen particles
  const edm::RefProd<TtGenEvent> & genEvent() const { return genEvt_; };
  const reco::GenParticle* genHadronicTop() const { return !genEvt_ ? 0 : this->genEvent()->hadronicDecayTop(); };
  const reco::GenParticle* genHadronicW()   const { return !genEvt_ ? 0 : this->genEvent()->hadronicDecayW(); };
  const reco::GenParticle* genHadronicB()   const { return !genEvt_ ? 0 : this->genEvent()->hadronicDecayB(); };
  const reco::GenParticle* genHadronicP()   const { return !genEvt_ ? 0 : this->genEvent()->hadronicDecayQuarkBar(); };
  const reco::GenParticle* genHadronicQ()   const { return !genEvt_ ? 0 : this->genEvent()->hadronicDecayQuark(); };
  const reco::GenParticle* genLeptonicTop() const { return !genEvt_ ? 0 : this->genEvent()->leptonicDecayTop(); };
  const reco::GenParticle* genLeptonicW()   const { return !genEvt_ ? 0 : this->genEvent()->leptonicDecayW(); };
  const reco::GenParticle* genLeptonicB()   const { return !genEvt_ ? 0 : this->genEvent()->leptonicDecayB(); };
  const reco::GenParticle* genLepton()      const { return !genEvt_ ? 0 : this->genEvent()->singleLepton();   };
  const reco::GenParticle* genNeutrino()    const { return !genEvt_ ? 0 : this->genEvent()->singleNeutrino(); };
  
  // access meta information
  bool isHypoValid(const HypoKey& key) const { return isHypoAvailable(key) ? !eventHypo(key).roles().empty() : false;}
  bool isHypoAvailable(const HypoKey& key) const { return evtHyp_.find(key)!=evtHyp_.end();};
  unsigned int numberOfAvailableHypos() const { return evtHyp_.size();};
  std::vector<int> jetMatch(const HypoKey& key) const { return jetMatch_.find(key)->second; };
  double genMatchSumPt() const { return genMatchSumPt_; };
  double genMatchSumDR() const { return genMatchSumDR_; };
  std::string mvaMethod() const { return mvaDisc_.first; }
  double mvaDisc() const { return mvaDisc_.second; }
  double fitChi2() const { return fitChi2_; }
  double fitProb() const { return fitProb_; }

 public:

  // set decay
  void setDecay(const Decay& dec) { decay_=dec; };

  // set the generated event
  void setGenEvent(const edm::Handle<TtGenEvent>& evt) { genEvt_=edm::RefProd<TtGenEvent>(evt); };

  // add EventHypotheses
  void addEventHypo(const HypoKey& key, reco::NamedCompositeCandidate hyp) { evtHyp_[key]=hyp; };
  
  // set meta information
  void addJetMatch(const HypoKey& key, const std::vector<int>& match) { jetMatch_[key]=match; };
  void setGenMatchSumPt(const double& val) {genMatchSumPt_=val;};
  void setGenMatchSumDR(const double& val) {genMatchSumDR_=val;};
  void setMvaDiscAndMethod(const std::string& name, const double& val) {mvaDisc_=std::pair<std::string, double>(name, val);};
  void setFitChi2(const double& val) { fitChi2_=val; };
  void setFitProb(const double& val) { fitProb_=val; };

 private:

  // event content
  Decay decay_;
  edm::RefProd<TtGenEvent> genEvt_;
  std::map<HypoKey, reco::NamedCompositeCandidate> evtHyp_;
  
  //meta information
  std::map<HypoKey, std::vector<int> > jetMatch_;
  double fitChi2_;                          // result of kinematic fit
  double fitProb_;                          // result of kinematic fit
  double genMatchSumPt_;                    // result of gen match
  double genMatchSumDR_;                    // result of gen match
  std::pair<std::string, double> mvaDisc_;  // result of MVA discriminant
};

#endif