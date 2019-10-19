//Coded in C++
//C++
//C++
//C++



#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <fstream>


using namespace std;



class minHeapNode
{
public:
    char data;
    int freq;
    char representative;
    minHeapNode * left;
    minHeapNode * right;
    minHeapNode(char data, int freq) : data(data), freq(freq), representative(data), left(NULL), right(NULL) {}
};

class myComparator
{
public:
    int operator() (const minHeapNode * p1, const minHeapNode * p2)
    {
        if(p1 -> freq == p2 -> freq)
            return p1 -> representative >= p2 -> representative; // ASCII cmoparison
        else return p1 -> freq > p2 -> freq;
    }
};


minHeapNode * buildHuffmanTree(map<char, int> & file)
{
    priority_queue<minHeapNode* , vector<minHeapNode*>, myComparator> minHeap;
    map<char, int> :: iterator it;
    for (auto it : file)
    {
        minHeap.push(new minHeapNode(it.first, it.second));
    }
    
    while (minHeap.size() != 1)
    {
        minHeapNode * first = minHeap.top();
        minHeap.pop();
        minHeapNode * second = minHeap.top();
        minHeap.pop();
        if (first-> representative > second->representative) {
            minHeapNode * temp = first;
            first = second;
            second = temp;
        }
        minHeapNode * N1 = new minHeapNode('$', first -> freq + second -> freq);
        N1 -> left = first;
        N1 -> right = second;
        if(N1-> left->representative > N1 -> right -> representative){
            N1 -> representative=N1 -> right -> representative;
        }
        else
        N1 -> representative=N1 -> left -> representative;
        minHeap.push(N1);
    }
    
    return minHeap.top();
}

void getCodes(minHeapNode * root, string code, map<char, string> & codes)
{
    if(!root)
    {
        return;
    }
    if (root -> data != '$')
    {
        codes.insert({root -> data, code});
    }
    getCodes(root -> left, code + '0', codes);
    getCodes(root -> right, code + '1', codes);
}

string decode_file(minHeapNode * root, string code)
{
    string ans = "";
    minHeapNode * curr = root;
    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] == '0')
        {
            curr = curr -> left;
        }
        else curr = curr -> right;
        if (!curr -> left && !curr -> right)
        {
            ans += curr -> data;
            curr = root;
        }
    }
    return ans + '\0';
}

void levelOrderTraversal(minHeapNode * root)
{
    queue<minHeapNode*> q;
    q.push(root);
    q.push(NULL);
    while (1)
    {
        minHeapNode * top = q.front();
        q.pop();
        if(!top)
        {
            cout << endl;
            if(q.empty())
                break;
            q.push(NULL);
        }
        else
        {
            cout << top -> data << " : " << top -> representative << "\t";
            if(top -> left)
                q.push(top -> left);
            if(top -> right)
                q.push(top -> right);
        }
    }
}

int main(int argm, char* argv[])
{
    string filename = argv[1];
    ifstream inFile;
    inFile.open(filename);
    string text="";
    string x;
    if (!inFile) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    
    while (getline(inFile, x)) {
        text = text + x;
    }
    
    map<char, int> file;
    for (int i = 0; i < text.size(); i++)
    {
        if (file.count(text[i]) == 0)
        {
            file[text[i]] = 1;
        }
        else file[text[i]]++;
    }
    inFile.close();
    minHeapNode * root = buildHuffmanTree(file);
    map<char, string> codes;
    getCodes(root, "", codes);
    
    
    ofstream outFile;
    outFile.open("code.txt");
    
    
    for(auto it : codes)
    {
        if (it.first==' '){
            outFile << "Space" << ": " << it.second  ;
        }
        else{
            outFile << it.first << ": " << it.second  ;
        }
        outFile<<endl;
        
    }
    ofstream out;
    out.open("encodemsg.txt");
    
    
    string encoded = "";
   
    int counter=0;
    
     for (int i = 0; i < text.length(); i++)
    {
        for(int j=0;j<codes.at(text[i]).length();j++){
            
           
            if(counter!=80){
                out<<codes.at(text[i])[j];
                
            }
            else{
                out<<endl<<codes.at(text[i])[j];
                
                counter=0;
            }
            counter++;
        }
    
        encoded += codes.at(text[i]);
        
    }
    float size = float(encoded.size());
    outFile<< "Ave = " << round (1.0 * size * 100/ text.size())/100 <<" bits per symbol";
    outFile.close();
    out.close();
    
}
