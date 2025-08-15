#include <iostream>
#include <vector>
#include <string>
#include<fstream>

using namespace std;

//document element can be either text or image element
//open to extention as it can have tab element, newline element
class DocumentElement{
public:
     virtual string render()=0;
};

class TextElement: public DocumentElement{
     private:
     string text;

     public:
     TextElement(string text){
          this->text=text;
     }
     string render() override{
          return text;
     }
};

class ImgElement: public DocumentElement{
     private:
     string imgPath;

     public:
     ImgElement(string imgPath){
          this->imgPath=imgPath;
     }
     string render() override{
          return imgPath;
     }
};

// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabSpaceElement : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};


class Document{
private:
     vector<DocumentElement*> elements;

public:
     void addElement(DocumentElement * element){
          elements.push_back(element);
     }

     //takes an element object from vector and calls its render method 
     string render(){ 
          string result;
          for(auto ele: elements){
               result += ele->render();
          }
          return result;
     }
};


class Persistence{
     public:
     
     // virtual method save can be of different types filestorage, mysql etc 
     virtual void save(string data)=0;
};

class FileStorage: public Persistence{
     void save(string data) override{
          ofstream file("file.txt");
          if(file){
               file << data;
               file.close();
               cout<< "written to file file.txt"<<'\n';
          }else{
               cout<<"Unable to open the file"<<endl;
          }
     }
};
class MongoStorage: public Persistence{
     void save(string data) override{
          cout<< "data written on mongo db sucessfully"<<endl;
     }
};


class DocumentEditor{
     public: 
     Document * doc;
     Persistence * db;
     string renderedDocument;

     DocumentEditor( Persistence* p){
          doc=new Document();
          this->db=p; 
     }

     void addText( string text){
          doc->addElement(new TextElement (text));
     }

     void addImg(string imgPath){
          doc->addElement(new ImgElement(imgPath));
     }

     string render(){
          if(renderedDocument.empty()){
               renderedDocument=doc->render();
          }
          return doc->render();
     }

     void save(){
          db->save(render());
     }

};

int main(){

     DocumentEditor * googleDocs=new DocumentEditor(new FileStorage());
     googleDocs->addText("hello World");
     googleDocs->addImg("Cat.png");

     cout<< googleDocs->render();

     return 0;
}



