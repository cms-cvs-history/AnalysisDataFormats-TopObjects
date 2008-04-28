//
// $Id: TopElectron.cc,v 1.3.2.3 2008/04/24 08:23:45 rwolf Exp $
//

#include "AnalysisDataFormats/TopObjects/interface/TopElectron.h"


/// default constructor
TopElectron::TopElectron() : TopLepton<TopElectronType>() {
}


/// constructor from TopElectronType
TopElectron::TopElectron(const TopElectronType & anElectron) : TopLepton<TopElectronType>(anElectron) {
}


/// destructor
TopElectron::~TopElectron() {
}


/// return the tracker isolation variable
double TopElectron::getTrackIso() const {
  return trackIso_;
}


/// return the calorimeter isolation variable
double TopElectron::getCaloIso() const {
  return caloIso_;
}


/// return the lepton ID discriminator
double TopElectron::getLeptonID(int idx) const {
  if(Robust<=idx && idx<=Tight){
    return leptonIDsCut_[idx];
  }
  else{ //leptonID idx is outof scope
    return -1.;
  }
}

double TopElectron::getLeptonIDTDR(int idx) const {
  if(Robust<=idx && idx<=Tight){
    return leptonIDsTDR_[idx];
  }
  else{ //leptonID idx is outof scope
    return -1.;
  }
}

/// return the cut based electron ids
double TopElectron::getLeptonID() const {
  return getLeptonID( Tight );
}

double TopElectron::getLeptonIDCutRobust() const {
  return getLeptonID( Robust );
}

double TopElectron::getLeptonIDCutLoose() const {
  return getLeptonID( Loose );
}

double TopElectron::getLeptonIDCutTight() const {
  return getLeptonID( Tight  );
}

/// return the tdr based electron ids
double TopElectron::getLeptonIDTDR() const {
  return getLeptonIDTDR( Tight );
}

double TopElectron::getLeptonIDTDRLoose() const {
  return getLeptonIDTDR( Robust );
}

double TopElectron::getLeptonIDTDRMedium() const {
  return getLeptonIDTDR( Loose );
}

double TopElectron::getLeptonIDTDRTight() const {
  return getLeptonIDTDR( Tight  );
}

/// return tracker isolation as calc. by Egamma POG producer
double TopElectron::getEgammaTkIso() const {
  return egammaTkIso_;
}

/// return "number of tracks" isolation as calc. by Egamma POG producer
int TopElectron::getEgammaTkNumIso() const {
  return egammaTkNumIso_;
}

/// return ecal isolation as calc. by Egamma POG producer
double TopElectron::getEgammaEcalIso() const {
  return egammaEcalIso_;
}

/// return hcal isolation as calc. by Egamma POG producer
double TopElectron::getEgammaHcalIso() const {
  return egammaHcalIso_;
}

/// method to set the tracker isolation variable
void TopElectron::setTrackIso(double trackIso) {
  trackIso_ = trackIso;
}


/// method to set the calorimeter isolation variable
void TopElectron::setCaloIso(double caloIso) {
  caloIso_ = caloIso;
}


/// methods to set the lepton ID discriminator
void TopElectron::setLeptonID(std::vector<double> ids) {
  if(ids.size()==maxElecID){
    leptonIDsCut_ = ids;
  }
}

void TopElectron::setLeptonIDCutRobust(double id) {
  if(leptonIDsCut_.capacity()<maxElecID) leptonIDsCut_.reserve(maxElecID);
  leptonIDsCut_[Robust]=id;
}

void TopElectron::setLeptonIDCutLoose(double id) {
  if(leptonIDsCut_.capacity()<maxElecID) leptonIDsCut_.reserve(maxElecID);
  leptonIDsCut_[Loose]=id;
}

void TopElectron::setLeptonIDCutTight (double id) {
  if(leptonIDsCut_.capacity()<maxElecID) leptonIDsCut_.reserve(maxElecID);
  leptonIDsCut_[Tight ]=id;
}

/// method to set the tdr style electron id
void TopElectron::setLeptonIDTDR(std::vector<double> ids) {
  if(ids.size()==maxElecID){
    leptonIDsTDR_ = ids;
  }
}

void TopElectron::setLeptonIDTDRLoose(double id) {
  if(leptonIDsTDR_.capacity()<maxElecID) leptonIDsTDR_.reserve(maxElecID);
  leptonIDsTDR_[Robust]=id;
}

void TopElectron::setLeptonIDTDRMedium(double id) {
  if(leptonIDsTDR_.capacity()<maxElecID) leptonIDsTDR_.reserve(maxElecID);
  leptonIDsTDR_[Loose]=id;
}

void TopElectron::setLeptonIDTDRTight (double id) {
  if(leptonIDsTDR_.capacity()<maxElecID) leptonIDsTDR_.reserve(maxElecID);
  leptonIDsTDR_[Tight ]=id;
}

/// methods to set the isolation from the Egamma POG's producer
void TopElectron::setEgammaTkIso(double iso) {
  egammaTkIso_=iso;
}
void TopElectron::setEgammaTkNumIso(int iso) {
  egammaTkNumIso_=iso;
}
void TopElectron::setEgammaEcalIso(double iso) {
  egammaEcalIso_=iso;
}
void TopElectron::setEgammaHcalIso(double iso) {
  egammaHcalIso_=iso;
}
