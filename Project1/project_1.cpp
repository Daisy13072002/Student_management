#include <iostream>
using namespace std;
#include <string>
#include <fstream>
//Create Sinhvien Struct
struct Sinhvien
{
private:
    string tenSV;
    string maSV;
    float diemTB;
public:
    //Declare constructor
    Sinhvien() {}
    Sinhvien(string tenSV, string maSV, float diemTB)
    {
        this->tenSV = tenSV;
        this->maSV = maSV;
        this->diemTB = diemTB;
    }
    //Setter and Getter
    void settenSV(string tenSV)
    {
        this->tenSV = tenSV;
    }

    string gettenSV()
    {
        return tenSV;
    }

    void setmaSV(string maSV)
    {
        this->maSV = maSV;
    }

    string getmaSV()
    {
        return maSV;
    }

    void setdiemTB(float diemTB)
    {
        this->diemTB = diemTB;
    }

    float getdiemTB()
    {
        return diemTB;
    }
    //function display and enter your code 
    void Hienthi()
    {
        cout << "Ten: " << gettenSV() << ", Ma: " << getmaSV() << ", Diem: " << getdiemTB() << endl;
    }

    void Nhap()
    {
        cout << "Nhap ten Sinh vien: ";
        cin.ignore();
        getline(cin, tenSV);
        settenSV(tenSV);


        cout << "Nhap ma so Sinh vien: ";
        getline(cin, maSV);
        setmaSV(maSV);


        cout << "Nhap diem trung binh: ";
        cin >> diemTB;
        setdiemTB(diemTB);
    }
};

struct node
{
    Sinhvien* data;
    node* next;
};
//Create newnode
node* Creatnode(Sinhvien* x)
{
    node* newnode = new node;
    newnode->data = x;
    newnode->next = NULL;
    return newnode;
}

// Thêm sinh viên vào danh sách
void add(node*& head, Sinhvien* x)
{
    node* newnode = Creatnode(x);
    if (head == NULL)
    {
        head = newnode;
        return;
    }
    node* tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = newnode;
}

// Hiển thị danh sách sinh viên
void Hienthidanhsach(node* head)
{
    if (head == NULL)
    {
        cout << "Danh sach rong!" << endl;
        return;
    }
    while (head != NULL)
    {
        head->data->Hienthi();
        head = head->next;
    }
}

// Tìm kiếm sinh viên theo mã số
void search(node* head)
{
    if (head == NULL)
    {
        cout << "Danh sach rong!" << endl;
        return;
    }

    string maSV;
    cout << "Nhap ma Sinhvien can tim kiem: ";
    cin >> maSV;

    node* tmp = head;
    bool found = false;

    while (tmp != NULL)
    {
        if (tmp->data->getmaSV() == maSV)
        {
            tmp->data->Hienthi();
            found = true;
            break;
        }
        tmp = tmp->next;
    }

    if (!found)
    {
        cout << "Khong tim thay ma sinh vien: " << maSV << endl;
    }
}

// Xóa sinh viên theo mã số
void deletemaSV(node*& head)
{
    if (head == NULL)
    {
        cout << "Danh sach rong!" << endl;
        return;
    }

    string maSV;
    cout << "Nhap ma Sinhvien can xoa: ";
    cin >> maSV;

    node* tmp = head;
    node* pre = NULL;

    // Xử lý nếu node đầu tiên là node cần xóa
    if (head->data->getmaSV() == maSV)
    {
        tmp = head;
        head = head->next;
        delete tmp;
        cout << "Da xoa sinh vien co ma " << maSV << endl;
        return;
    }

    // Xử lý các node còn lại
    while (tmp != NULL && tmp->data->getmaSV() != maSV)
    {
        pre = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        cout << "Khong tim thay ma sinh vien: " << maSV << endl;
        return;
    }

    pre->next = tmp->next;
    delete tmp;
    cout << "Da xoa sinh vien co ma " << maSV << endl;
}

// Đọc dữ liệu từ file và thêm vào danh sách
void Docdulieutufile(ifstream& filein, node*& head)
{
    string tenSV, maSV;
    float diemTB;
    while (!filein.eof())
    {
        if (filein.fail()) break;
        filein >> tenSV >> maSV >> diemTB;  // Đọc dữ liệu từ file

        Sinhvien* sv = new Sinhvien(tenSV, maSV, diemTB);  // Tạo đối tượng Sinhvien mới
        add(head, sv);  // Thêm vào danh sách liên kết
    }
    cout << "Da doc du lieu tu file.\n";
}

// Ghi dữ liệu ra file từ danh sách
void Ghidulieurafile(ofstream& fileout, node* head)
{
    while (head != NULL)
    {
        fileout << head->data->gettenSV() << " "
            << head->data->getmaSV() << " "
            << head->data->getdiemTB() << endl;
        head = head->next;
    }
    cout << "Da ghi du lieu ra file.\n";
}

int main()
{
    node* head = NULL;
    int choice;

    do {
        cout << "====================" << endl;
        cout << "1. Them sinh vien" << endl;
        cout << "2. Hien thi danh sach sinh vien" << endl;
        cout << "3. Tim kiem sinh vien" << endl;
        cout << "4. Xoa sinh vien" << endl;
        cout << "5. Doc du lieu tu file" << endl;
        cout << "6. Ghi du lieu ra file" << endl;
        cout << "7. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        // Kiểm tra xem lựa chọn có hợp lệ không
        if (choice < 1 || choice > 7)
        {
            cout << "Lua chon khong hop le! Vui long chon lai." << endl;
            continue;
        }

        switch (choice)
        {
        case 1: {
            Sinhvien* sv = new Sinhvien();
            sv->Nhap();
            add(head, sv);
            break;
        }
        case 2:
            Hienthidanhsach(head);
            break;
        case 3:
            search(head);
            break;
        case 4:
            deletemaSV(head);
            break;
        case 5: {
            ifstream filein("D:\\Dev\\visualStudio\\Project1\\Danhsach_Sinhvien.txt");
            if (filein.is_open())
            {
                Docdulieutufile(filein, head);
                filein.close();
            }
            else {
                cout << "Khong mo duoc file.\n";
            }
            break;
        }
        case 6: {
            ofstream fileout("D:\\Dev\\visualStudio\\Project1\\Danhsach_Sinhvien.txt");
            if (fileout.is_open())
            {
                Ghidulieurafile(fileout, head);
                fileout.close();
            }
            else {
                cout << "Khong mo duoc file.\n";
            }
            break;
        }
        case 7:
            cout << "Thoat chuong trinh." << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}

