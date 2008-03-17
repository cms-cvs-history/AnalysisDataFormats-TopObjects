//
// $Id: TopElectron.h,v 1.5 2008/01/25 13:32:13 vadler Exp $
//

#ifndef TopObjects_TopElectron_h
#define TopObjects_TopElectron_h

/**
  \class    TopElectron TopElectron.h "AnalysisDataFormats/TopObjects/interface/TopElectron.h"
  \brief    High-level top electron container

   TopElectron contains an electron as a TopObject, and provides the means to
   store and retrieve the high-level additional information.

  \author   Steven Lowette
  \version  $Id: TopElectron.h,v 1.5 2008/01/25 13:32:13 vadler Exp $
*/

#include "DataFormats/EgammaCandidates/interface/PixelMatchGsfElectron.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "AnalysisDataFormats/TopObjects/interface/TopLepton.h"


typedef reco::PixelMatchGsfElectron TopElectronType;
typedef reco::PixelMatchGsfElectronCollection TopElectronTypeCollection;


class TopElectron : public TopLepton<TopElectronType> {
  
  friend class TopElectronProducer;

 public:
  static const unsigned int maxElecID = 3;  

  enum elecID {
    Robust = 0,
    Medium = 1,
    Tight  = 2
  };
  
  TopElectron();
  TopElectron(const TopElectronType & anElectron);
  virtual ~TopElectron();
  
  double getTrackIso() const;
  double getCaloIso() const;
  double getLeptonID() const;
  double getLeptonID(int) const;
  double getLeptonIDCutRobust() const;
  double getLeptonIDCutMedium() const;
  double getLeptonIDCutTight()  const;
  double getLeptonIDTDR() const;
  double getLeptonIDTDR(int) const;
  double getLeptonIDTDRRobust() const;
  double getLeptonIDTDRMedium() const;
  double getLeptonIDTDRTight()  const;
  double getEgammaTkIso() const;
  int getEgammaTkNumIso() const;
  double getEgammaEcalIso() const;
  double getEgammaHcalIso() const;
  
  
 protected:
  
  void setTrackIso(double trackIso);
  void setCaloIso(double caloIso);
  void setLeptonID(std::vector<double> ids);
  void setLeptonIDCutRobust(double id);
  void setLeptonIDCutMedium(double id);
  void setLeptonIDCutTight (double id);
  void setLeptonIDTDR(std::vector<double> ids);
  void setLeptonIDTDRRobust(double id);
  void setLeptonIDTDRMedium(double id);
  void setLeptonIDTDRTight (double id);
  void setEgammaTkIso(double tkIso);
  void setEgammaTkNumIso(int tkNumIso);
  void setEgammaEcalIso(double ecalIso);
  void setEgammaHcalIso(double hcalIso);

 protected:
  

  double trackIso_;
  double caloIso_;
  std::vector<double> leptonIDsCut_;
  std::vector<double> leptonIDsTDR_;
  double egammaTkIso_;
  int egammaTkNumIso_;
  double egammaEcalIso_;
  double egammaHcalIso_;
};


#endif
