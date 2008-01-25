//
// $Id: TopJet.cc,v 1.16 2008/01/08 16:24:25 jandrea Exp $
//


#include "AnalysisDataFormats/TopObjects/interface/TopJet.h"


/// default constructor
TopJet::TopJet() :
  TopObject<TopJetType>(TopJetType(reco::Particle::LorentzVector(0, 0, 0, 0), reco::Particle::Point(0,0,0), reco::CaloJet::Specific(), reco::Jet::Constituents())),
  jetFlavour_(0), lrPhysicsJetLRval_(-999.), lrPhysicsJetProb_(-1),
  jetCharge_(0.0), associatedTracks_() {
}


/// constructor from a TopJetType
TopJet::TopJet(TopJetType aJet) :
  TopObject<TopJetType>(aJet),
  jetFlavour_(0), lrPhysicsJetLRval_(-999.), lrPhysicsJetProb_(-1) {
}


/// destructor
TopJet::~TopJet() {
}


/// return the matched generated parton
reco::GenParticle TopJet::getGenParton() const {
  return (genParton_.size() > 0 ?
    genParton_.front() :
    reco::GenParticle(0, reco::GenParticle::LorentzVector(0, 0, 0, 0), reco::GenParticle::Point(0,0,0), 0, 0, true)
  );
}


/// return the matched generated jet
reco::GenJet TopJet::getGenJet() const {
  return (genJet_.size() > 0 ?
    genJet_.front() :
    reco::GenJet(reco::Particle::LorentzVector(0, 0, 0, 0), reco::Particle::Point(0,0,0), reco::GenJet::Specific(), reco::Jet::Constituents())
  );
}


/// return the flavour of the parton underlying the jet
int TopJet::getPartonFlavour() const {
  return jetFlavour_;
}


/// return the correction factor to go to a non-calibrated jet
float TopJet::getNoCorrF() const {
  return noCorrF_;
}


/// return the correction factor to go to a uds-calibrated jet
float TopJet::getUdsCorrF() const {
  return udsCorrF_;
}


/// return the correction factor to go to a gluon-calibrated jet
float TopJet::getGluCorrF() const {
  return gCorrF_;
}


/// return the correction factor to go to a c-calibrated jet
float TopJet::getCCorrF() const {
  return cCorrF_;
}


/// return the correction factor to go to a b-calibrated jet
float TopJet::getBCorrF() const {
  return bCorrF_;
}


/// return the associated non-calibrated jet
TopJetType TopJet::getRecJet() const {
  TopJetType recJet(*this);
  recJet.setP4(noCorrF_*this->p4());
  return recJet;
}


/// return the associated non-calibrated jet
TopJet TopJet::getNoCorrJet() const {
  TopJet jet(*this);
  jet.setP4(noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1., this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}


/// return the associated uds-calibrated jet
TopJet TopJet::getUdsCorrJet() const {
  TopJet jet(*this);
  jet.setP4(udsCorrF_*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1./this->getUdsCorrF(), this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}


/// return the associated gluon-calibrated jet
TopJet TopJet::getGluCorrJet() const {
  TopJet jet(*this);
  jet.setP4(gCorrF_*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1./this->getGluCorrF(), this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}


/// return the associated c-calibrated jet
TopJet TopJet::getCCorrJet() const {
  TopJet jet(*this);
  jet.setP4(cCorrF_*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1./this->getCCorrF(), this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}


/// return the associated b-calibrated jet
TopJet TopJet::getBCorrJet() const {
  TopJet jet(*this);
  // set the corrected 4-vector
  jet.setP4(bCorrF_*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1./this->getBCorrF(), this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  // set the resolutions assuming this jet to be a b-jet
  jet.setResA(bResA_);
  jet.setResB(bResB_);
  jet.setResC(bResC_);
  jet.setResD(bResD_);
  jet.setResET(bResET_);
  jet.setResEta(bResEta_);
  jet.setResPhi(bResPhi_);
  jet.setResTheta(bResTheta_);
  jet.setCovM(bCovM_);
  return jet;
}


/// return the jet calibrated according to the MC flavour truth
TopJet TopJet::getMCFlavCorrJet() const {
  // determine the correction factor to use depending on MC flavour truth
  float corrF = gCorrF_; // default, also for unidentified flavour
  if (abs(this->getPartonFlavour()) == 1 || abs(this->getPartonFlavour()) == 2 || abs(this->getPartonFlavour()) == 3) corrF = udsCorrF_;
  if (abs(this->getPartonFlavour()) == 4) corrF = cCorrF_;
  if (abs(this->getPartonFlavour()) == 5) corrF = bCorrF_;
  TopJet jet(*this);
  jet.setP4(corrF*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(1./corrF, this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}


/// return the jet calibrated with weights assuming W decay
TopJet TopJet::getWCorrJet() const {
  TopJet jet(*this);
  // set the corrected 4-vector weighting for the c-content in W decays
  jet.setP4((3*udsCorrF_+cCorrF_)/4*noCorrF_*this->p4());
  // fix the factor to uncalibrate for the fact that we change the scale of the actual jet
  jet.setScaleCalibFactors(4./(3*udsCorrF_+cCorrF_), this->getUdsCorrF(), this->getGluCorrF(), this->getCCorrF(), this->getBCorrF());
  return jet;
}



/// get b discriminant from label name
double TopJet::getBDiscriminator(std::string theLabel) const {
  double discriminator = -10.;
  if (theLabel == "default") theLabel = "trackCountingHighEffJetTags";
  if (theLabel == "") theLabel = "trackCountingHighEffJetTags";
  for(unsigned int i=0; i!=pairDiscriVector_.size(); i++){
    if(pairDiscriVector_[i].first == theLabel){
      discriminator = pairDiscriVector_[i].second;
    }
  }
  return discriminator;
}


/// get JetTagRef from labael name
reco::JetTagRef TopJet::getBJetTagRef(std::string theLabel) const {
  reco::JetTagRef theJetTagRef ;
  //if(pairDiscriJetTagRef.size() == 0){
  //  cout << "no JetTagRef found" << endl;
  //}
  for(unsigned int i=0; i!=pairJetTagRefVector_.size(); i++){
    if(pairJetTagRefVector_[i].first == theLabel){
       theJetTagRef= pairJetTagRefVector_[i].second;
    }
  } 
  return theJetTagRef;
}


/// write out all the labels present - FIXME: should use the message logger
void TopJet::dumpBTagLabels() const {
  if(pairDiscriVector_.size() == 0){
    std::cout << "no Label found" << std::endl;
  }
  for(unsigned int i=0; i!=pairDiscriVector_.size(); i++){
    std::cout << "Label : " << pairDiscriVector_[i].first << std::endl;
  }
}


/// get the value of the i'th jet cleaning variable
double TopJet::getLRPhysicsJetVar(unsigned int i) const {
  return (i < lrPhysicsJetVarVal_.size() ? lrPhysicsJetVarVal_[i].first  : 0);
}


/// get the likelihood ratio corresponding to the i'th jet cleaning variable
double TopJet::getLRPhysicsJetVal(unsigned int i) const {
  return (i < lrPhysicsJetVarVal_.size() ? lrPhysicsJetVarVal_[i].second : 1);
}


/// get the overall jet cleaning likelihood ratio
double TopJet::getLRPhysicsJetLRval() const {
  return lrPhysicsJetLRval_;
}


/// get the overall jet cleaning probability
double TopJet::getLRPhysicsJetProb() const {
  return lrPhysicsJetProb_;
}


/// method to set the matched parton
void TopJet::setGenParton(const reco::GenParticle & gp) {
  genParton_.clear();
  genParton_.push_back(gp);
}


/// method to set the matched generated jet
void TopJet::setGenJet(const reco::GenJet & gj) {
  genJet_.clear();
  genJet_.push_back(gj);
}


/// method to set the flavour of the parton underlying the jet
void TopJet::setPartonFlavour(int jetFl) {
  jetFlavour_ = jetFl;
}


/// method to set the energy scale correction factors
void TopJet::setScaleCalibFactors(float noCorrF, float udsCorrF, float gCorrF, float cCorrF, float bCorrF) {
  noCorrF_ = noCorrF;
  udsCorrF_ = udsCorrF;
  gCorrF_ = gCorrF;
  cCorrF_ = cCorrF;
  bCorrF_ = bCorrF;
}


/// method to set the resolutions under the assumption this is a b-jet
void TopJet::setBResolutions(float bResET, float bResEta, float bResPhi, float bResA, float bResB, float bResC, float bResD, float bResTheta) {
  bResET_ = bResET;
  bResEta_ = bResEta;
  bResPhi_ = bResPhi;
  bResA_ = bResA;
  bResB_ = bResB;
  bResC_ = bResC;
  bResD_ = bResD;
  bResTheta_ = bResTheta;
}


/// method to add a algolabel-discriminator pair
void TopJet::addBDiscriminatorPair(std::pair<std::string, double> & thePair) {
  pairDiscriVector_.push_back(thePair);
}


/// method to add a algolabel-jettagref pair
void TopJet::addBJetTagRefPair(std::pair<std::string, reco::JetTagRef> & thePair) {
  pairJetTagRefVector_.push_back(thePair);
}


/// method to set all jet cleaning variable + LR pairs
void TopJet::setLRPhysicsJetVarVal(const std::vector<std::pair<double, double> > & varValVec) {
  for (size_t i = 0; i<varValVec.size(); i++) lrPhysicsJetVarVal_.push_back(varValVec[i]);
}


/// method to set the combined jet cleaning likelihood ratio value
void TopJet::setLRPhysicsJetLRval(double clr) {
  lrPhysicsJetLRval_ = clr;
}


/// method to set the jet cleaning probability
void TopJet::setLRPhysicsJetProb(double plr) {
  lrPhysicsJetProb_  = plr;
}

/// method to return the JetCharge computed when creating the TopJet
float TopJet::getJetCharge() const {
  return jetCharge_;
}

/// method to return a vector of refs to the tracks associated to this jet
const reco::TrackRefVector & TopJet::getAssociatedTracks() const {
  return associatedTracks_;
}
