#include <QDebug>
#include "lismodel.h"

LisModel::LisModel(QObject *parent)
    : QObject(parent)
{
}

LisModel::LisModel(const QString &session_n, const QString &session_s,const QString session_d,const QString session_e,QString session_p, QObject *parent)
    : QObject(parent), session_n_(session_n),session_s_(session_s),session_d_(session_d),session_e_(session_e),session_p_(session_p)
{
}
 void LisModel::setSession_n(const QString &sesn){
     if (sesn != this->session_n_) {
         this->session_n_ = sesn;
         emit session_n_changed();
     }
}
 void LisModel::setSession_s(const QString &sess){
     if (sess != this->session_s_) {
         this->session_s_ = sess;
         emit session_s_changed();
     }
}
 void LisModel::setSession_d(const QString &sesd){
     if (sesd != this->session_d_) {
         this->session_d_ = sesd;
         emit session_d_changed();
     }
}
 void LisModel::setSession_e(const QString &sese){
     qDebug()<<sese;
     if (sese != this->session_e_) {
         this->session_e_ = sese;
         emit session_e_changed();
     }
}
 void LisModel::setSession_p(const QString &sesp){
     if (sesp != this->session_p_) {
         this->session_p_ = sesp;
         emit session_p_changed();
     }
}
 QString LisModel::session_n() const{
  return session_n_;
 }
 QString LisModel::session_s() const{
return session_s_;
 }
 QString LisModel::session_d() const{
return session_d_;
 }
 QString LisModel::session_e() const{
return session_e_;
 }
 QString LisModel::session_p() const{
return session_p_;
 }









