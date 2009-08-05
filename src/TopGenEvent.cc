#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "PhysicsTools/CandUtils/interface/pdgIdUtils.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "AnalysisDataFormats/TopObjects/interface/TopGenEvent.h"


/// default contructor
TopGenEvent::TopGenEvent(reco::GenParticleRefProd& parts, reco::GenParticleRefProd& inits)
{
  parts_ = parts; 
  initPartons_= inits;
}

const reco::GenParticle*
TopGenEvent::candidate(int id) const
{
  const reco::GenParticle* cand=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for (unsigned int i = 0; i < partsColl.size(); ++i) {
    if (partsColl[i].pdgId()==id) {
      cand = &partsColl[i];
    }
  }  
  return cand;
}

void
TopGenEvent::print() const 
{
  edm::LogVerbatim log("TopGenEvent");
  log << "\n"
      << "--------------------------------------\n"
      << "- Dump TopGenEvent Content           -\n"
      << "--------------------------------------\n";
  for (reco::GenParticleCollection::const_iterator part = parts_->begin(); 
       part<parts_->end(); ++part) {
    log << "pdgId:"  << std::setw(5)  << part->pdgId()     << ", "
	<< "mass:"   << std::setw(11) << part->p4().mass() << ", "
	<< "energy:" << std::setw(11) << part->energy()    << ", " 
	<< "pt:"     << std::setw(11) << part->pt()        << "\n"; 
  }
}

int
TopGenEvent::numberOfLeptons(bool fromWBoson) const
{
  int lep=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for (unsigned int i = 0; i < partsColl.size(); ++i) {
    if (reco::isLepton(partsColl[i])) {
      if(fromWBoson){
	if(partsColl[i].mother() &&  abs(partsColl[i].mother()->pdgId())==TopDecayID::WID){
	  ++lep;
	}
      }
      else{
	++lep;
      }
    }
  }  
  return lep;
}

int
TopGenEvent::numberOfLeptons(WDecay::LeptonType typeRestriction, bool fromWBoson) const
{
  int leptonType=-1;
  switch(typeRestriction){
    // resolve whether or not there is
    // any restriction in lepton types
  case WDecay::kElec: 
    leptonType=TopDecayID::elecID;
    break;
  case WDecay::kMuon: 
    leptonType=TopDecayID::muonID;
    break;
  case WDecay::kTau: 
    leptonType=TopDecayID::tauID;
    break;
  case WDecay::kNone:
    break;
  }
  int lep=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for(unsigned int i = 0; i < partsColl.size(); ++i) {
    if(fromWBoson){
      // restrict to particles originating from the W boson
      if( !(partsColl[i].mother() &&  abs(partsColl[i].mother()->pdgId())==TopDecayID::WID) ){
	continue;
      }
    }
    if(leptonType>0){
      // in case of lepton type restriction
      if( abs(partsColl[i].pdgId())==leptonType ){
	++lep;
      }
    }
    else{
      // take any lepton type into account else
      if( reco::isLepton(partsColl[i]) ){
	++lep;
      }
    }
  }  
  return lep;
}

int
TopGenEvent::numberOfBQuarks(bool fromTopQuark) const
{
  int bq=0;
  const reco::GenParticleCollection & partsColl = *parts_;
  for (unsigned int i = 0; i < partsColl.size(); ++i) {
    if (abs(partsColl[i].pdgId())==TopDecayID::bID) {
      if(fromTopQuark){
	if(partsColl[i].mother() &&  abs(partsColl[i].mother()->pdgId())==TopDecayID::tID){
	  ++bq;
	}
      }
      else{
	++bq;
      }
    }
  }  
  return bq;
}

std::vector<const reco::GenParticle*> 
TopGenEvent::topSisters() const
{
  std::vector<const reco::GenParticle*> sisters;
  for(reco::GenParticleCollection::const_iterator part = parts_->begin(); part<parts_->end(); ++part){
    if( part->numberOfMothers()==0 && abs(part->pdgId())!= TopDecayID::tID){
      // choose top sister which do not have a 
      // mother and are whether top nor anti-top 
      if( dynamic_cast<const reco::GenParticle*>( &(*part) ) == 0){
	throw edm::Exception( edm::errors::InvalidReference, "Not a GenParticle" );
      }
      sisters.push_back( part->clone() );
    }
  }  
  return sisters;
}

std::vector<const reco::GenParticle*> 
TopGenEvent::lightQuarks(bool bIncluded) const 
{
  std::vector<const reco::GenParticle*> lightQuarks;
  reco::GenParticleCollection::const_iterator part = parts_->begin();
  for ( ; part < parts_->end(); ++part) {
    if( (bIncluded && abs(part->pdgId())==TopDecayID::bID) || abs(part->pdgId())<TopDecayID::bID ) {
      if( dynamic_cast<const reco::GenParticle*>( &(*part) ) == 0){
	throw edm::Exception( edm::errors::InvalidReference, "Not a GenParticle" );
      }
      lightQuarks.push_back( part->clone() );
    }
  }  
  return lightQuarks;
}

std::vector<const reco::GenParticle*> 
TopGenEvent::radiatedGluons(int pdgId) const{
  std::vector<const reco::GenParticle*> rads;
  for (reco::GenParticleCollection::const_iterator part = parts_->begin(); part < parts_->end(); ++part) {
    if(part->pdgId()==TopDecayID::glueID){
      if ( part->mother() && part->mother()->pdgId()==pdgId ){
	if( dynamic_cast<const reco::GenParticle*>( &(*part) ) == 0){
	  throw edm::Exception( edm::errors::InvalidReference, "Not a GenParticle" );
	}
	rads.push_back( part->clone() );
      }
    }
  }  
  return rads;
}

