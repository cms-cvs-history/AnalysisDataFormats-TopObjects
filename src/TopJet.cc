// -*- C++ -*-
//
// Package:     TopJet
// Class  :     TopJet
// 
// Implementation:
//     <Notes on implementation>
//
// Original Author:  
//         Created:  Wed May 10 11:48:25 CEST 2006
// $Id: TopJet.cc,v 1.1 2007/05/22 16:36:50 heyninck Exp $
//

// system include files

// user include files
#include "AnalysisDataFormats/TopObjects/interface/TopJet.h"

TopJet::TopJet(){ 
  lrPhysicsJetLRval	= -999.;
  lrPhysicsJetProb	= -999.;
}

TopJet::TopJet(JetType aJet): TopObject<JetType>(aJet) {
  lrPhysicsJetLRval	= -999.;
  lrPhysicsJetProb	= -999.;
}

TopJet::~TopJet(){ }

void 		TopJet::setGenJet(reco::Particle gj)  	{ genJet = gj; }
void 		TopJet::setRecJet(JetType rj)     	{ recJet = rj; }
void 		TopJet::setFitJet(TopParticle fj) 	{ fitJet = fj; }
void 		TopJet::setBdiscriminant(double b)	{ bdiscr = b; }
void 		TopJet::setLRPhysicsJetVarVal(std::vector<std::pair<double, double> > varval) { for(size_t i = 0; i<varval.size(); i++) lrPhysicsJetVarVal.push_back(varval[i]); }
void 		TopJet::setLRPhysicsJetLRval(double clr) {lrPhysicsJetLRval = clr;}
void 		TopJet::setLRPhysicsJetProb(double plr)  {lrPhysicsJetProb  = plr;}

reco::Particle	TopJet::getGenJet() const	  	{ return genJet; }
JetType		TopJet::getRecJet() const	  	{ return recJet; }
TopParticle	TopJet::getFitJet() const	  	{ return fitJet; }
double   	TopJet::getBdiscriminant() const 	{ return bdiscr; }
double          TopJet::getLRPhysicsJetVar(unsigned int i) const { return (i < lrPhysicsJetVarVal.size() ? lrPhysicsJetVarVal[i].first  : 0); } 
double          TopJet::getLRPhysicsJetVal(unsigned int i) const { return (i < lrPhysicsJetVarVal.size() ? lrPhysicsJetVarVal[i].second : 1); }
double          TopJet::getLRPhysicsJetLRval() const 	{ return lrPhysicsJetLRval; }
double          TopJet::getLRPhysicsJetProb() const 	{ return lrPhysicsJetProb; }