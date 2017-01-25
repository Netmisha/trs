#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) :
    QStandardItemModel(parent)
{


    m_roleNameMapping[MyTreeModel_Role_Name] = "name_role";
    db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("D:\\TRS\\TBox\\TestInfo.db");
            db.setHostName("127.0.0.1");
             if(db.open()){
                 qDebug()<<"Database: connection ok";
             }
             else{
                 qDebug()<<db.lastError().text();
             }

}
/*void TreeModel::ConnectToDb(){

}*/
void TreeModel::FillTreeData(QStandardItem *root_node){
    QSqlQuery q("select * from Info LIMIT 0,0 ");
          QSqlRecord rec = q.record();
          for(int i=0;i<rec.count();i++){
              db_col.append(rec.fieldName(i));
          }

          q.exec("select * from Info");
          while(q.next()){
              QSqlRecord rec = q.record();
              QStringList tmp;
              for(int i=0;i<rec.count();i++){
                  tmp<<rec.value(i).toString();
              }
              tmp.removeFirst();
              db_list.append(tmp);

          }

          for(int i=0;i<rec.count();i++){
              if(rec.fieldName(i) == "ID"){
              node n;
              n.curr = new QStandardItem(rec.fieldName(i));
              n.index = this->indexFromItem(n.curr);
              n.name = rec.fieldName(i);
              leaf.push_back(n);
              root_node->appendRow(n.curr);
                QSqlQuery query;
                 QString queryString = "SELECT Test_Name FROM Info";
                 query.exec(queryString);
                 QStringList tn;
                 while (query.next()) {
                     QSqlRecord record = query.record();
                     tn.append(record.value("Test_Name").toString());
                 }
                 std::sort(tn.begin(),tn.end());
                 tn.erase( std::unique(tn.begin(),tn.end()),tn.end()); // remove duplicates
              }

          }

           /*
          for( int i=0;i<rec.count();i++){ // db column names
              filt = new QStandardItem(rec.fieldName(i));
              root_node->appendRow(filt);
          }
           */
          /*foreach(auto &var,db_list){ // db data
              rep = new QStandardItem(var.join(" "));
              root_node->appendRow(rep);
          }*/


}
void TreeModel::add_root(){
    QStandardItem *root = new QStandardItem(QString("Report_data"));
    this->appendRow(root);
    FillTreeData(root);
}




QHash<int, QByteArray> TreeModel::roleNames() const
{
    return m_roleNameMapping;
}
