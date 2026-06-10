#include <iostream>
#include <vector> // 負責使用動態陣列（std::vector），用來儲存未知數量的商品
#include <string> // 負責處理字串型態（std::string）與字串切片工具 
#include <algorithm> // 負責提供高效的排序演算法（std::sort）
#include <fstream> // 負責檔案讀寫功能（std::ifstream） 

using namespace std;

// 定義商品的結構
struct Product {
 string name; // 商品名稱 
 int expiration; // 剩餘有效期限 
 int popularity; // 熱門程度
};

// 比較函式
// 如果兩個商品的效期不同，效期越近的要放在越顯眼的位置，所以使用小於比較
bool compareProducts(const Product& a, const Product& b) {
 if (a.expiration != b.expiration) {
  return a.expiration < b.expiration;
 }
    
 // 如果兩個商品的效期相同
 // 則看熱門程度，越熱門的要放在越顯眼的位置，所以使用大於比較
 return a.popularity > b.popularity;
}

int main() {
 ifstream infile("input.txt"); // 宣告檔案輸入流物件，並嘗試開啟同資料夾下的 "input.txt"檔案 
    
 // 如果路徑錯了或檔案不存在，infile.is_open() 會回傳 false
 if (!infile.is_open()) {
  cerr << "【錯誤】無法開啟 input.txt！" << endl;
  cerr << "請確認 input.txt 檔案是否與此程式碼編譯後的 .exe 檔案放在同一個資料夾中。" << endl;
  return 1; // 回傳 1 代表程式異常終止 
 }

 int n; // 用來儲存商品總數量 
 // 從檔案讀取第一個整數（商品數量 N）。如果讀取失敗，就結束程式。
 if (!(infile >> n)) return 0;
 infile.ignore(); // 忽略數字後的換行符

 vector<Product> products; // 宣告一個 Vector 動態陣列，用來放置所有讀入並解析完畢的商品物件 
 for (int i = 0; i < n; ++i) {
  string line;
        
  // 使用 getline 讀取檔案的一整行資料（包含字串中間的空格）
  // 如果讀不到東西，就跳出迴圈 
  if (!getline(infile, line)) break;
        
  // 從字串的最尾端開始往前找最後一個空格的位置
  size_t last_space = line.find_last_of(' ');
  if (last_space == string::npos) continue;  // 安全防護：找不到空格就跳過這行 
        
  // 擷取最後一個空格後面的子字串，並利用 stoi (String to Integer) 轉成整數
  int popularity = stoi(line.substr(last_space + 1));
        
  // 切除掉最後的熱度部分，留下剩下的前半段字串
  string remaining = line.substr(0, last_space);
        
  // 在剩下的字串中，再次從尾端尋找最後一個空格
  size_t second_last_space = remaining.find_last_of(' ');
  if (second_last_space == string::npos) continue; // 安全防護
        
  // 擷取這個空格後面的子字串，轉成整數
  int expiration = stoi(remaining.substr(second_last_space + 1));
         
  // 剩下的最前段，不管中間有多少空格，都一定屬於商品的完整名稱
  string name = remaining.substr(0, second_last_space);
        
  products.push_back({name, expiration, popularity}); // 將解析出來的 名稱、效期、熱度 包裝成 Product 結構，推入 Vector 陣列中
 }

 // 當所有資料都讀取並放入記憶體後，關閉檔案，釋放系統資源
 infile.close();

 // 呼叫標準庫的高效排序並執行 
 sort(products.begin(), products.end(), compareProducts);

 // 使用 Range-based for loop（範圍基礎迴圈）依序取出排序後的每個商品
 // const auto& 代表使用唯讀且引用的方式讀取，避免複製結構體，提升效能。
 cout << "商品排序:" << endl;
 for (const auto& prod : products) {
  cout << prod.name << endl; // 輸出題目要求的商品名稱 
 }

 return 0;
}
