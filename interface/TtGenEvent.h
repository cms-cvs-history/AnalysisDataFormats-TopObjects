#ifndef TopObjects_TtGenEvent_h
#define TopObjects_TtGenEvent_h

#include "PhysicsTools/CandUtils/interface/pdgIdUtils.h"
#include "AnalysisDataFormats/TopObjects/interface/TopGenEvent.h"


namespace TtFullLepEvtPartons{
  /// full leptonic parton enum used to define the order 
  /// in the vector for lepton jet combinatorics; this 
  /// order has to be obeyed strictly then!
  enum { B, BBar, Lepton, LeptonBar };
}

namespace TtSemiLepEvtPartons{
  /// semi-leptonic parton enum used to define the order 
  /// in the vector for lepton jet combinatorics; this 
  /// order has to be obeyed strictly then!
  enum { LightQ, LightQBar, HadB, LepB, Lepton };
}

namespace TtFullHadEvtPartons{
  /// full hadronic parton enum used to define the order 
  /// in the vector for lepton jet combinatorics; this 
  /// order has to be obeyed strictly then!
  enum { LightQTop, LightQBarTop, B, LightQTopBar, LightQBarTopBar, BBar};
}


// ----------------------------------------------------------------------
// derived class for: 
//
//  * TtGenEvent
//
//  the structure holds reference information to the generator particles 
//  of the decay chains for each top quark and of the initial partons 
//  and provides access and administration;  the derived class contains 
//  a few additional getters with respect to its base class
// ----------------------------------------------------------------------

class TtGenEvent: public TopGenEvent {

 public:

  /// empty constructor  
  TtGenEvent() {};
  /// default constructor
  TtGenEvent(reco::GenParticleRefProd&, reco::GenParticleRefProd&);
  /// default destructor
  virtual ~TtGenEvent() {};

  /// check if the event can be classified as ttbar
  bool isTtBar() const {return (top() && topBar());}
  /// check if the event can be classified as full hadronic
  bool isFullHadronic(bool excludeTauLeptons=true) const { return isTtBar() ? isNumberOfLeptons(excludeTauLeptons, 0) : false;}
  /// check if the event can be classified as semi-laptonic
  bool isSemiLeptonic(bool excludeTauLeptons=true) const { return isTtBar() ? isNumberOfLeptons(excludeTauLeptons, 1) : false;}
  /// check if the event can be classified as full leptonic
  bool isFullLeptonic(bool excludeTauLeptons=true) const { return isTtBar() ? isNumberOfLeptons(excludeTauLeptons, 2) : false;}

  /// return decay channel; all leptons including taus are allowed 
  WDecay::LeptonType semiLeptonicChannel() const;
  /// check if the event is semi-leptonic with the lepton being of typeA; all leptons including taus are allowed
  bool isSemiLeptonic(WDecay::LeptonType typeA) const { return semiLeptonicChannel()==typeA ? true : false; };
  /// check if the event is semi-leptonic with the lepton being of typeA or typeB; all leptons including taus are allowed
  bool isSemiLeptonic(WDecay::LeptonType typeA, WDecay::LeptonType typeB) const { return (semiLeptonicChannel()==typeA || semiLeptonicChannel()==typeB)? true : false; };
  // return decay channel (as a std::pair of LeptonType's); all leptons including taus are allowed
  std::pair<WDecay::LeptonType, WDecay::LeptonType> fullLeptonicChannel() const;
  /// check if the event is full leptonic with the lepton being of typeA or typeB irrelevant of order; all leptons including taus are allowed
  bool isFullLeptonic(WDecay::LeptonType typeA, WDecay::LeptonType typeB) const;

  /// return single lepton if available; 0 else
  const reco::GenParticle* singleLepton(bool excludeTauLeptons=true) const;
  /// return single neutrino if available; 0 else
  const reco::GenParticle* singleNeutrino(bool excludeTauLeptons=true) const;
  /// get W of leptonic decay branch
  const reco::GenParticle* leptonicDecayW(bool excludeTauLeptons=true) const;
  /// get b of leptonic decay branch
  const reco::GenParticle* leptonicDecayB(bool excludeTauLeptons=true) const;
  /// get top of leptonic decay branch
  const reco::GenParticle* leptonicDecayTop(bool excludeTauLeptons=true) const;
  /// get W of hadronic decay branch
  const reco::GenParticle* hadronicDecayW(bool excludeTauLeptons=true) const;
  /// get b of hadronic decay branch
  const reco::GenParticle* hadronicDecayB(bool excludeTauLeptons=true) const;
  /// get top of hadronic decay branch
  const reco::GenParticle* hadronicDecayTop(bool excludeTauLeptons=true) const;
  /// get light quark of hadronic decay branch
  const reco::GenParticle* hadronicDecayQuark(bool invert=false) const;
  /// get light anti-quark of hadronic decay branch
  const reco::GenParticle* hadronicDecayQuarkBar() const {return hadronicDecayQuark(true); };
  /// gluons as radiated from the leptonicly decaying top quark
  std::vector<const reco::GenParticle*> leptonicDecayTopRadiation(bool excludeTauLeptons=true) const;
  /// gluons as radiated from the hadronicly decaying top quark
  std::vector<const reco::GenParticle*> hadronicDecayTopRadiation(bool excludeTauLeptons=true) const;
  /// get lepton for semi-leptonic or full leptonic decays
  const reco::GenParticle* lepton(bool excludeTauLeptons=true) const;
  /// get anti-lepton for semi-leptonic or full leptonic decays
  const reco::GenParticle* leptonBar(bool excludeTauLeptons=true) const;
  /// get neutrino for semi-leptonic or full leptonic decays
  const reco::GenParticle* neutrino(bool excludeTauLeptons=true) const;
  /// get anti-neutrino for semi-leptonic or full leptonic decays
  const reco::GenParticle* neutrinoBar(bool excludeTauLeptons=true) const;
  /// get light quark from top for full hadronic decays
  const reco::GenParticle* lightQFromTop() const;
  /// get light anti-quark from top for full hadronic decays
  const reco::GenParticle* lightQBarFromTop() const;
  /// get light quark from anti-top for full hadronic decays
  const reco::GenParticle* lightQFromTopBar() const;
  /// get light anti-quark from anti-top for full hadronic decays
  const reco::GenParticle* lightQBarFromTopBar() const;

 private:

  /// check whether the number of leptons among the daughters of the W boson is nlep
  /// or not; there is an option to exclude taus from the list of leptons to consider
  bool isNumberOfLeptons(bool excludeTauLeptons, int nlep) const {return excludeTauLeptons ? (numberOfLeptons()-numberOfLeptons(WDecay::kTau))==nlep : numberOfLeptons()==nlep;}
};

inline const reco::GenParticle* 
TtGenEvent::lepton(bool excludeTauLeptons) const 
{ 
  return (singleLepton(excludeTauLeptons) && reco::flavour(*singleLepton(excludeTauLeptons))>0) ? singleLepton(excludeTauLeptons) : 0; 
}

inline const reco::GenParticle* 
TtGenEvent::leptonBar(bool excludeTauLeptons) const 
{ 
  return (singleLepton(excludeTauLeptons) && reco::flavour(*singleLepton(excludeTauLeptons))<0) ? singleLepton(excludeTauLeptons) : 0; 
}

inline const reco::GenParticle* 
TtGenEvent::neutrino(bool excludeTauLeptons) const 
{ 
  return (singleNeutrino(excludeTauLeptons) && reco::flavour(*singleNeutrino(excludeTauLeptons))>0) ? singleLepton(excludeTauLeptons) : 0; 
}

inline const reco::GenParticle* 
TtGenEvent::neutrinoBar(bool excludeTauLeptons) const 
{ 
  return (singleNeutrino(excludeTauLeptons) && reco::flavour(*singleNeutrino(excludeTauLeptons))<0) ? singleLepton(excludeTauLeptons) : 0; 
}

inline bool
TtGenEvent::isFullLeptonic(WDecay::LeptonType typeA, WDecay::LeptonType typeB) const
{
  return ( (fullLeptonicChannel().first==typeA && fullLeptonicChannel().second==typeB)||
	   (fullLeptonicChannel().first==typeB && fullLeptonicChannel().second==typeA));
}

#endif
