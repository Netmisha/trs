#ifndef LISMODEL_H
#define LISMODEL_H
#include <QObject>
#include <qDebug>
class LisModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString session_n READ session_n WRITE setSession_n NOTIFY session_n_changed)
    Q_PROPERTY(QString session_s READ session_s WRITE setSession_s NOTIFY session_s_changed)
    Q_PROPERTY(QString session_d READ session_d WRITE setSession_d NOTIFY session_d_changed)
    Q_PROPERTY(QString session_e READ session_e WRITE setSession_e NOTIFY session_e_changed)
    Q_PROPERTY(QString session_p READ session_p WRITE setSession_p NOTIFY session_p_changed)

public:
   LisModel(QObject *parent=0);
   LisModel(const QString &session_n, const QString &session_s,const QString session_d,const QString session_e,QString session_p, QObject *parent=0);
    QString session_n() const;
    QString session_s() const;
    QString session_d() const;
    QString session_e() const;
    QString session_p() const;
   Q_INVOKABLE void setSession_n(const QString &sesn);
   Q_INVOKABLE void setSession_s(const QString &sess);
   Q_INVOKABLE void setSession_d(const QString &sesd);
   Q_INVOKABLE void setSession_e(const QString &sese);
   Q_INVOKABLE void setSession_p(const QString &sesp);
 signals: // just in case
    void session_n_changed();
     void session_s_changed();
      void session_d_changed();
       void session_e_changed();
        void session_p_changed();
private:
   Q_INVOKABLE QString session_n_;
   Q_INVOKABLE QString session_s_;
   Q_INVOKABLE QString session_d_;
   Q_INVOKABLE QString session_e_;
   Q_INVOKABLE QString session_p_;


};

#endif // LisModel_H
