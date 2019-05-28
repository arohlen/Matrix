#ifndef MATRIX_H
#include <iostream>
using namespace std;

template <class T>
class Matris {
public:
   // constructors
   Matris (){
       static_assert(std::is_move_assignable<T>::value, "Needs to be move assignable");
       static_assert(std::is_move_constructible<T>::value, "Need to be move constructable");

       this->m_rows = 0;
       this->m_cols = 0;
       this->m_capacity = 0;
       this->m_vec = new T[0]();
   }
   explicit Matris (int rows, int cols){
       static_assert(std::is_move_assignable<T>::value, "Needs to be move assignable");
       static_assert(std::is_move_constructible<T>::value, "Need to be move constructable");

       this->m_rows = rows;
       this->m_cols = cols;
       this->m_capacity = rows*cols;
       this->m_vec = new T[rows*cols]();
   }
   explicit Matris (int rowcol){
       static_assert(std::is_move_assignable<T>::value, "Needs to be move assignable");
       static_assert(std::is_move_constructible<T>::value, "Need to be move constructable");

       this->m_rows = rowcol;
       this->m_cols = rowcol;
       this->m_capacity = rowcol*rowcol;
       this->m_vec = new T[rowcol*rowcol]();
   }
   Matris (const Matris &rhs){
       static_assert(std::is_move_assignable<T>::value, "Needs to be move assignable");
       static_assert(std::is_move_constructible<T>::value, "Need to be move constructable");

       this->m_rows = rhs.m_rows;
       this->m_cols = rhs.m_cols;
       this->m_capacity = rhs.m_rows*rhs.m_cols;
       this->m_vec = new T[rhs.m_rows*rhs.m_cols]();

       for (size_t i = 0; i < rhs.m_rows*rhs.m_cols; i++) {
           this->m_vec[i] = rhs.m_vec[i];
       }
   }
   Matris (std::initializer_list<T> l) {
       static_assert(std::is_move_assignable<T>::value, "Needs to be move assignable");
       static_assert(std::is_move_constructible<T>::value, "Need to be move constructable");

       this->m_vec = new T[l.size()]();

       for (size_t i = 0; i < l.size(); i++) {
           m_vec[i] = l.begin()[i];
       }

         this->m_rows = sqrt(l.size());
         this->m_cols = sqrt(l.size());
         this->m_capacity = l.size();
    }

    Matris (Matris&& rhs)
 	{
 		 this->m_vec = rhs.m_vec;
         this->m_rows = rhs.m_rows;
         this->m_cols = rhs.m_cols;
         this->m_capacity = rhs.m_rows*rhs.m_cols;

 		rhs.m_vec = nullptr;
 	}

    ~Matris(){
        delete [] this->m_vec;
    }

   // operators
   template<typename Y>
   friend istream & operator >> (istream &,  Matris<Y> &);

   T& operator() (const int row, const int col){
       return this->m_vec[(this->m_cols)*row+col];
   }

   const T& operator() (const int row, const int col) const{
       return this->m_vec[(this->m_cols)*row+col];
   }

   Matris& operator= (Matris &rhs){
       this->m_rows = rhs.m_rows;
       this->m_cols = rhs.m_cols;
       delete [] this->m_vec;

       this->m_vec = new T[rhs.m_capacity]();

       for (size_t i = 0; i < rhs.m_capacity; i++) {
           this->m_vec[i] = rhs.m_vec[i];
       }
       return *this;
   }

   bool operator== (Matris &rhs){
     bool equal = true;
     if (this->m_rows == rhs.m_rows && this->m_cols == rhs.m_cols) {
       for (size_t i = 0; i < this->m_capacity; i++) {
         if (this->m_vec[i] != rhs.m_vec[i]) {
           equal = false;
           break;
         }
       }
     }else{
       equal = false;
     }
     return equal;
   }

   Matris& operator= (Matris&& rhs)
	{
		// Self-assignment detection
		if (&rhs == this)
			return *this;

		delete this->m_vec;

		// Transfer ownership
		this->m_vec = rhs.m_vec;
        this->m_rows = rhs.m_rows;
        this->m_cols = rhs.m_cols;

		rhs.m_vec = nullptr;

		return *this;
	}

   Matris operator+= (Matris &rhs){

       if (this->m_rows == rhs.m_rows && this->m_cols == rhs.m_cols) {
           for (size_t i = 0; i < this->m_capacity; i++) {
               this->m_vec[i] += rhs.m_vec[i];
           }
           return *this;

       }else{
           throw std::out_of_range("Dimensions do not match");
       }


   }

   Matris operator+= (T rhs){


           for (size_t i = 0; i < this->m_capacity; i++) {
               this->m_vec[i] += rhs;
           }
           return *this;

   }

   Matris operator-= (Matris &rhs){

       if (this->m_rows == rhs.m_rows && this->m_cols == rhs.m_cols) {
           for (size_t i = 0; i < this->m_capacity; i++) {
               this->m_vec[i] -= rhs.m_vec[i];
           }
           return *this;

       }else{
           throw std::out_of_range("Dimensions do not match");
       }
   }

   Matris operator-= (T rhs){


           for (size_t i = 0; i < this->m_capacity; i++) {
               this->m_vec[i] -= rhs;
           }
           return *this;

   }

   Matris operator*= (Matris & rhs){
       if (this->m_cols == rhs.m_rows) {
           Matris<T> m = Matris<T>(this->m_rows,rhs.m_cols);
           T result = 0;

           for (unsigned int i = 0; i < this->m_rows; i++) {
               for (unsigned int j = 0; j <  rhs.m_cols; j++) {
                   for (unsigned int k = 0; k < rhs.m_rows; k++) {

                       result += (this->m_vec[(this->m_cols)*i+k] * rhs(k,j));
                   }
                    m(i,j) = result;
                    result = 0;
               }
           }

           this->m_rows = m.m_rows;
           this->m_cols = m.m_cols;
           delete [] this->m_vec;
           this->m_vec = new T(m.m_rows*m.m_cols);

          for (size_t i = 0; i < m.m_rows*m.m_cols; i++) {
              this->m_vec[i] = m.m_vec[i];
          }

          return *this;

       }else{
           throw std::out_of_range("Dimensions do not match");
       }

   }

   Matris operator*= (T rhs){


           for (size_t i = 0; i < this->m_capacity; i++) {
               this->m_vec[i] *= rhs;
           }
           return *this;

   }

   Matris operator* (Matris & rhs){

       if (this->m_cols == rhs.m_rows) {
           Matris<T> m = Matris<T>(this->m_rows,rhs.m_cols);
           T result = 0;

           for (unsigned int i = 0; i < this->m_rows; i++) {
               for (unsigned int j = 0; j <  rhs.m_cols; j++) {
                   for (unsigned int k = 0; k < rhs.m_rows; k++) {

                       result += (this->m_vec[(this->m_cols)*i+k] * rhs(k,j));

                   }
                    m(i,j) = result;
                    result = 0;
               }
           }

           return m;

       }else{
           throw std::out_of_range("Dimensions do not match");
       }

   }

   Matris operator* (T rhs){
          Matris<T> m = Matris<T>(this->m_rows,this->m_cols);

           for (size_t i = 0; i < this->m_capacity; i++) {
               m.m_vec[i] = this->m_vec[i] * rhs;
           }
           return m;

   }

   Matris operator+(Matris &rhs) {
       if (this->m_rows == rhs.m_rows && this->m_cols == rhs.m_cols) {

            Matris<T> m = Matris<T>(this->m_rows,rhs.m_cols);

           for(unsigned int i = 0; i < this->m_capacity; i++) {
                m.m_vec[i] = this->m_vec[i] + rhs.m_vec[i];
           }
           return m;

       }else{
           throw std::out_of_range("Dimensions do not match");
       }

    }

    Matris operator+ (T rhs){

            Matris<T> m = Matris<T>(this->m_rows,this->m_cols);

            for (size_t i = 0; i < this->m_capacity; i++) {
                m.m_vec[i] = this->m_vec[i] + rhs;
            }
            return m;

    }

    Matris operator-(Matris &rhs) {
        if (this->m_rows == rhs.m_rows && this->m_cols == rhs.m_cols) {

             Matris<T> m = Matris<T>(this->m_rows,rhs.m_cols);

            for(unsigned int i = 0; i < this->m_capacity; i++) {
                 m.m_vec[i] = this->m_vec[i] - rhs.m_vec[i];
            }
            return m;

        }else{
            throw std::out_of_range("Dimensions do not match");
        }

     }

     Matris operator- (T rhs){

             Matris<T> m = Matris<T>(this->m_rows,this->m_cols);

             for (size_t i = 0; i < this->m_capacity; i++) {
                 m.m_vec[i] = this->m_vec[i] - rhs;
             }
             return m;

     }


   // methods
   const unsigned int cols(){
       return this->m_cols;
   }
   const unsigned int rows(){
       return this->m_rows;
   }

   const T* begin(){
       return this->m_vec;
   }

   const T* end(){
       return (this->m_vec)+(this->m_rows)*(this->m_cols);
   }

   void insert_row(unsigned int row){

       T* insert = new T[this->m_capacity+this->m_cols]();
       unsigned int j = 0;

       for (size_t i = 0; i < this->m_capacity; i++) {

           if (i == row*this->m_cols) {
               j += this->m_cols;
           }
           insert[j] = this->m_vec[i];
           j++;
       }
       delete [] this->m_vec;
       this->m_rows += 1;
       this->m_capacity += this->m_cols;
       this->m_vec = insert;
   }

   void append_row(){

       T* insert = new T[this->m_capacity+this->m_cols]();

       for (size_t i = 0; i < this->m_capacity; i++) {
           insert[i] = this->m_vec[i];
       }
       delete [] this->m_vec;
       this->m_rows += 1;
       this->m_capacity += this->m_cols;
       this->m_vec = insert;
   }

   void remove_row(unsigned int row){

       T* insert = new T[this->m_capacity-this->m_cols]();
       unsigned int j = 0;

       for (size_t i = 0; i < this->m_capacity-this->m_cols; i++) {

           if (i == row*this->m_cols) {
               j += this->m_cols;
           }
           insert[i] = this->m_vec[j];
           j++;
       }
       delete [] this->m_vec;
       this->m_rows -= 1;
       this->m_capacity -= this->m_cols;
       this->m_vec = insert;

   }
   void insert_column(unsigned int col){
       T* insert = new T[this->m_capacity+this->m_rows]();

       unsigned int j = 0;

       for (size_t i = 0; i < this->m_capacity; i++) {

           if (i == col) {
               j++;
               col += this->m_cols;
           }
           insert[j] = this->m_vec[i];
           j++;
       }
       delete [] this->m_vec;
       this->m_cols += 1;
       this->m_capacity += this->m_rows;
       this->m_vec = insert;

   }
   void append_column(){
       T* insert = new T[this->m_capacity+this->m_rows]();

       unsigned int compare = this->m_cols;
       unsigned int j = 0;

       for (size_t i = 0; i < this->m_capacity; i++) {

           if (i == compare) {
               j++;
               compare += this->m_cols;
           }
           insert[j] = this->m_vec[i];
           j++;
       }
       delete [] this->m_vec;
       this->m_cols += 1;
       this->m_capacity += this->m_rows;
       this->m_vec = insert;

   }
   void remove_column(unsigned int col){
       T* insert = new T[this->m_capacity-this->m_rows]();
       unsigned int j = 0;

       for (size_t i = 0; i < this->m_capacity-this->m_rows; i++) {

           if (j == col) {
               j++;
               col += this->m_cols;
           }
           insert[i] = this->m_vec[j];
           j++;
       }
       delete [] this->m_vec;
       this->m_cols -= 1;
       this->m_capacity -= this->m_rows;
       this->m_vec = insert;
   }
   void reset(){

        T* new_vec = new T[this->m_capacity]();
       delete [] this->m_vec;
       this->m_vec = new_vec;
   }

   void transpose(){
       T* list = new T[this->m_capacity];
       for (size_t i = 0; i < this->m_rows; i++) {
           for (size_t j = 0; j < this->m_cols; j++) {
               list[this->m_rows*j+i] = this->m_vec[this->m_cols*i+j];
           }
       }
       delete [] this->m_vec;
       int row = this->m_rows;
       this->m_rows = this->m_cols;
       this->m_cols = row;
       this->m_vec = list;
   }

private:
   size_t m_rows;
   size_t m_cols;
   size_t m_capacity;
   T * m_vec;
};

template<typename T>
ostream & operator << (ostream &out, Matris<T> m)
{
    out << m.rows() << " " << m.cols() << '\n' << '\n';
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.cols(); j++) {
            out << m(i,j) << " ";
        }
        out << '\n';
    }
    return out;
}


template<typename T>
istream & operator >> (istream &in,  Matris<T> &m){
    unsigned int rows;
    unsigned int cols;
    T element;
    in >> rows;
    in >> cols;
    m.m_rows = rows;
    m.m_cols = cols;
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < cols; col++) {
            in >> element;
            m(row,col) = element;
        }
    }
    return in;
}

template<typename T>
Matris<T> identity(unsigned int size){
    Matris<T> m(size);
    unsigned int j = 0;
    for (unsigned int i = 0; i < m.rows(); i++) {
        m(i,j) = 1;
        j++;
    }
    return m;
}

#endif
