//
// Author:  Steven Lowette
// Created: Wed May  2 16:48:32 PDT 2007
//
// $Id: TopLepton.h,v 1.1 2007/05/03 01:37:10 lowette Exp $
//

#ifndef TopLepton_h
#define TopLepton_h

/**
  \class    TopLepton TopLepton.h "AnalysisDataFormats/TopObjects/interface/TopLepton.h"
  \brief    High-level top lepton container

   TopLepton contains a lepton as a TopObject, and provides the means to
   store and retrieve the high-level likelihood ratio information.

  \author   Steven Lowette
  \version  $Id$
*/


#include "DataFormats/EgammaCandidates/interface/PixelMatchGsfElectron.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "AnalysisDataFormats/TopObjects/interface/TopObject.h"


typedef reco::PixelMatchGsfElectron ElectronType;
typedef reco::Muon MuonType;


template <class LeptonType>
class TopLepton : public TopObject<LeptonType> {

  friend class TopLeptonLRCalc;

  public:

    TopLepton() {}
    TopLepton(LeptonType aLep): TopObject<LeptonType>(aLep) {}
    virtual ~TopLepton() {}

    double getLRVar(unsigned int i);
    double getLRVal(unsigned int i);
    double getLRComb();

  protected:

    unsigned int getLRSize();
    void setLRVarVal(std::pair<double, double> lrVarVal, unsigned int i);
    void setLRComb(double lr);

  protected:

    double lrComb_;
    std::vector<std::pair<double, double> > lrVarVal_;

};


template <class LeptonType> double TopLepton<LeptonType>::getLRVar(unsigned int i) { return (i < lrVarVal_.size() ? lrVarVal_[i].first  : 0); }
template <class LeptonType> double TopLepton<LeptonType>::getLRVal(unsigned int i) { return (i < lrVarVal_.size() ? lrVarVal_[i].second : 1); }
template <class LeptonType> double TopLepton<LeptonType>::getLRComb() { return lrComb_; }
template <class LeptonType> unsigned int TopLepton<LeptonType>::getLRSize() { return lrVarVal_.size(); }
template <class LeptonType> void TopLepton<LeptonType>::setLRVarVal(std::pair<double, double> lrVarVal, unsigned int i) {
  while (lrVarVal_.size() <= i) lrVarVal_.push_back(std::pair<double, double>(0, 1));
  lrVarVal_[i] = lrVarVal;
}
template <class LeptonType> void TopLepton<LeptonType>::setLRComb(double lr) { lrComb_ = lr; }


typedef TopLepton<ElectronType> TopElectron;
typedef TopLepton<MuonType> TopMuon;


#endif
