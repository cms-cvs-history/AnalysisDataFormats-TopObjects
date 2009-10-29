#ifndef TopObjects_TtFullHadronicEvent_h
#define TopObjects_TtFullHadronicEvent_h

#include "AnalysisDataFormats/TopObjects/interface/TtEvent.h"

namespace TtFullHadDaughter{
  /// full hadronic daughter names for common
  /// use and use with the hypotheses
  static const std::string LightQ   ="LightQ"   , LightP="LightP", WPlus ="WPlus" , B   ="B"   , Top   ="Top";
  static const std::string LightQBar="LightQBar", LightPBar   ="LightPBar"   , WMinus="WMinus", BBar="BBar", TopBar="TopBar"; 
}

/**
   \class   TtFullHadronicEvent TtFullHadronicEvent.h "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

   \brief   Class derived from the TtEvent for the full hadronic decay channel

   The structure holds information on the hadronic decay channels, 
   all event hypotheses of different classes (user defined during
   production) and a reference to the TtGenEvent (if available). It 
   provides access and administration.
*/

class TtFullHadronicEvent: public TtEvent {
  
 public:
  /// empty constructor
  TtFullHadronicEvent(){};
  /// default destructor
  virtual ~TtFullHadronicEvent(){};

  /// get top of the given hypothesis
  const reco::Candidate* top(const std::string& key, const unsigned& cmb=0) const { return top(hypoClassKeyFromString(key), cmb); };
  /// get top of the given hypothesis
  const reco::Candidate* top(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : eventHypo(key,cmb). daughter(TtFullHadDaughter::Top); };
  /// get b of the given hypothesis
  const reco::Candidate* b(const std::string& key, const unsigned& cmb=0) const { return b(hypoClassKeyFromString(key), cmb); };
  /// get b of the given hypothesis
  const reco::Candidate* b(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : top(key,cmb)->daughter(TtFullHadDaughter::B); };
  /// get Wplus of the given hypothesis
  const reco::Candidate* wPlus(const std::string& key, const unsigned& cmb=0) const { return wPlus(hypoClassKeyFromString(key), cmb); };
  /// get Wplus of the given hypothesis
  const reco::Candidate* wPlus(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : top(key,cmb)->daughter(TtFullHadDaughter::WPlus); };

  /// get anti-top of the given hypothesis
  const reco::Candidate* topBar(const std::string& key, const unsigned& cmb=0) const { return topBar(hypoClassKeyFromString(key), cmb); };
  /// get anti-top of the given hypothesis
  const reco::Candidate* topBar(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : eventHypo(key,cmb). daughter(TtFullHadDaughter::TopBar); };
  /// get anti-b of the given hypothesis
  const reco::Candidate* bBar(const std::string& key, const unsigned& cmb=0) const { return bBar(hypoClassKeyFromString(key), cmb); };
  /// get anti-b of the given hypothesis
  const reco::Candidate* bBar(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : topBar(key,cmb)->daughter(TtFullHadDaughter::BBar  ); };
  /// get Wminus of the given hypothesis
  const reco::Candidate* wMinus(const std::string& key, const unsigned& cmb=0) const { return wMinus(hypoClassKeyFromString(key), cmb); };
  /// get Wminus of the given hypothesis
  const reco::Candidate* wMinus(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : topBar(key,cmb)->daughter(TtFullHadDaughter::WMinus); };

  /// get top of the TtGenEvent
  const reco::GenParticle* top        () const { return (!genEvt_ ? 0 : this->genEvent()->top()        ); };
  /// get b of the TtGenEvent
  const reco::GenParticle* b          () const { return (!genEvt_ ? 0 : this->genEvent()->b()          ); };
  /// get Wplus of the TtGenEvent
  const reco::GenParticle* wPlus      () const { return (!genEvt_ ? 0 : this->genEvent()->wPlus()      ); };

  /// get anti-top of the TtGenEvent
  const reco::GenParticle* topBar     () const { return (!genEvt_ ? 0 : this->genEvent()->topBar()     ); };
  /// get anti-b of the TtGenEvent
  const reco::GenParticle* bBar       () const { return (!genEvt_ ? 0 : this->genEvent()->bBar()       ); };
  /// get Wminus of the TtGenEvent
  const reco::GenParticle* wMinus     () const { return (!genEvt_ ? 0 : this->genEvent()->wMinus()     ); };

  /// print full content of the structure as formated 
  /// LogInfo to the MessageLogger output for debugging  
  void print();
};

#endif
