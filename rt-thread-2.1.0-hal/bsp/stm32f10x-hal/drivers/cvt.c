

#include "cvt.h"
#include <math.h>
#include <stdint.h>


void * my_strcpy(void *dst, const void *src, unsigned int strlen)
{
   if(!(dst && src)) 
     return 0;
   char * pchdst = (char*)dst;
   char * pchsrc = (char*)src;
   while(strlen--) 
     *pchdst++ = *pchsrc++;
   
   return dst;
}

//float 转 int
int ftol(float f)
{ 
    int a         = *(int*)(&f);
    int sign      = (a>>31); 
    int mantissa  = (a&((1<<23)-1))|(1<<23);
    int exponent  = ((a&0x7fffffff)>>23)-127;
    int r         = ((unsigned int)(mantissa)<<8)>>(31-exponent);
    return ((r ^ (sign)) - sign ) &~ (exponent>>31);       
}

//double 转 int
union luai_Cast { double l_d; long l_l; };

#define dtol(i,d)  { volatile union luai_Cast u; \
   u.l_d = (d) + 6755399441055744.0; (i) = u.l_l; }

//字符串转整数
int StrToInt(char *str)
{
    
    int n = 0;	
    char *p = (char*)str;
    if(*p == '-') p++;
    while('0' <= *p && *p <= '9')		
        n = n * 10 + *p++ - '0';	
    if(*str == '-')       
        n = -n;
    return n;
}
/*
//下面的程序考虑了八进制、十进制、十六进制的字符串。
int StrToInt(char * str)
{ 
   int value = 0;
   int sign = 1;
   int radix;

   if(*str == '-')
   {
      sign = -1;
      str++;
   }

   if(*str == '0' && (*(str+1) == 'x' || *(str+1) == 'X'))
   {
      radix = 16;
      str += 2;
   }
   else if(*str == '0')
   {
      radix = 8;
      str++;
   }
   else
      radix = 10;
   while(*str)
   {
      if(radix == 16)
      {
        if(*str >= '0' && *str <= '9')
           value = value * radix + *str - '0';
        else
           value = value * radix + (*str | 0x20) - 'a' + 10;
      }
      else
        value = value * radix + *str - '0';
      str++;
   }
   return sign*value;
}*/

/*
void IntToStr(int value, char* str)
{
    
}*/

//字符串转浮点数
float StrToFloat(char* pstrfloat) 
{ 
    unsigned char bNegative = 0; 
    unsigned char bDec = 0; 
 
    char* pSor = 0; 
    char chByte = '0'; 
    float fInteger = 0.0; 
    float fDecimal = 0.0; 
    float fDecPower = 0.1f; 
 
 
		// check  
    if (!pstrfloat) 
    { 
        return 0.0; 
    } 
		
    // 进行首位判断，判断是否是负数 
    if (pstrfloat[0] == '-') 
    {  
        bNegative = 1; 
        pSor = pstrfloat + 1; 
    } 
    else 
    { 
        bNegative = 0; 
        pSor = pstrfloat; 
    } 

    while (*pSor != '\0') 
    { 
        chByte = *pSor; 
        if (bDec) 
        { 
            // 小数 
            if (chByte >= '0' && chByte <= '9') 
            { 
                fDecimal += (chByte - '0') * fDecPower; 
                fDecPower = fDecPower * 0.1; 
            } 
            else 
            { 
                return (bNegative? -(fInteger +  fDecimal): fInteger + fDecimal); 
            } 
        } 
        else 
        { 
            // 整数 
            if (chByte >= '0' && chByte <= '9') 
            { 
                fInteger = fInteger * 10.0 + chByte - '0'; 
            } 
            else if (chByte == '.') 
            { 
                bDec = 1; 
            } 
            else 
            { 
                return (bNegative? -fInteger : fInteger); 
            } 
        } 
        pSor++; 
    } 
    return (bNegative? -(fInteger +  fDecimal): fInteger + fDecimal); 
} 


//无符号短整型数组排序
//src---数组首地址，len数组长度(0~255)，up_down---0表示升序，---1表示降序
void bubble16(unsigned short *src, unsigned char len, unsigned char up_down)
{
   unsigned short tmp; 
   unsigned char i,j,unchange;
 
   if (up_down == 0)  //升序
   {
      for (i=0; i<len; i++)
      {
         unchange = 1;
         for (j=0; j<len-1-i; j++)
         {
            if (src[j] > src[j+1])
            {
               unchange = 0;
               tmp = src[j];
               src[j] = src[j+1];
               src[j+1] = tmp;
            }
         }
         if (unchange == 1) //不再有变化，无需再排
         break;
      }
   }
   else
   {
      for (i=0; i<len; i++)
      {
         unchange = 1;
         for (j=0; j<len-1-i; j++)
         {
            if (src[j] < src[j+1])
            {
               unchange = 0;
               tmp = src[j];
               src[j] = src[j+1];
               src[j+1] = tmp;
            }
         }
         if (unchange == 1) //不再有变化，无需再排
            break;
      }
   }
}
//无符号短整型数组排序
//src---数组首地址，len数组长度(0~255)，up_down---0表示升序，---1表示降序
void bubble32( unsigned int *src, unsigned char len, unsigned char up_down)
{
   uint32_t tmp; 
   unsigned char i,j,unchange;
 
   if (up_down == 0)  //升序
   {
      for (i = 0; i<len; i++)
      {
         unchange = 1;
         for (j = 0; j<len-1-i; j++)
         {
            if (src[j] > src[j+1])
            {
               unchange = 0;
               tmp = src[j];
               src[j] = src[j+1];
               src[j+1] = tmp;
            }
         }
         if (unchange == 1) //不再有变化，无需再排
         break;
      }
   }
   else
   {
      for (i=0; i<len; i++)
      {
         unchange = 1;
         for (j=0; j<len-1-i; j++)
         {
            if (src[j] < src[j+1])
            {
               unchange = 0;
               tmp = src[j];
               src[j] = src[j+1];
               src[j+1] = tmp;
            }
         }
         if (unchange == 1) //不再有变化，无需再排
            break;
      }
   }
}
//折半查找无符号元素
//在有序表R[1..n]中进行二分查找，成功时返回结点的位置，失败时返回-1
int BinSearch(unsigned short *src, unsigned char len, unsigned short key)
{       
   unsigned char low,high, mid;//置当前查找区间上、下界的初值
 
   while((len>1)&&(src[len-1]==0)) len--;
   low = 0;
   high = len-1;
   if((key < src[low])||(key > src[high]))//元素不在次表中
       return -1;
   if(key == src[low])
       return low;
   if(key == src[high])
       return high;
   while(low < high)//当前查找区间R[low..high]非空
   {
      mid = low + ((high-low)/2); //使用 (low + high) / 2 会有整数溢出的问题
   
      if(key == src[mid]) 
          return mid; //查找成功返回
   
      if(key < src[mid])
      {
         high = mid-1; //继续在R[low..mid-1]中查找
         if(key == src[high])//如果上边界的元素正是要找的元素
             return high;
      }
      else
      {
         low = mid+1; //继续在R[mid+1..high]中查找
         if(key == src[low])//如果下边界的元素正是要找的元素
             return low;
      }
    }
    return -1; //当low>high时表示查找区间为空，查找失败
} //BinSeareh

//二分插入法插入指定元素,前提是该队列至少有一个元素,删除成功后返回其位置
//在有序表R[1..n]中进行二分查找，成功时返回结点的位置，失败时返回-1
int BinSearchDelete(unsigned short *src, unsigned char len, unsigned short key)
{       
   unsigned char i, low,high,mid;//置当前查找区间上、下界的初值
   //先确定非零元素表长
     while((len>=1)&&(src[len-1]==0)) len--;
     low = 0;
     high = len-1;
   
   if((key < src[low])||(key > src[high]))//元素不在次表中
       return 0;
   if(key == src[low])//如果待删除的元素在表头
   {
      
      for(i=low;i<len-1;i++)//将此后面的元素前移
      {
          src[i] = src[i+1];
      }
      src[i] = 0;
      return low;
   }
   if(key == src[high])//如果在表尾，就直接删除
   {
       src[high] = 0;
       return high;
   }
   while(low < high)//当前查找区间R[low..high]非空
   {
      mid = low + ((high-low)/2); //使用 (low + high) / 2 会有整数溢出的问题   
      if(key == src[mid]) 
      {
          for(i=mid;i<len-1;i++)//其它元素前移
          {
              src[i] = src[i+1];
          }
          src[i] = 0;
          return mid; //返回删除的位置
      }
      if(key < src[mid])
      {
         high = mid-1; //继续在R[low..mid-1]中查找
         if(key == src[high])//如果上边界的元素正是要找的元素
         {    
            for(i=high;i<len-1;i++)//后面元素前移
            {
                src[i] = src[i+1];
            }
            src[i] = 0;    
            return high;//返回删除的位置
         }
      }
      else
      {
         low = mid+1; //继续在R[mid+1..high]中查找
         if(key == src[low])//如果下边界的元素正是要找的元素
         {
            for(i=low;i<len-1;i++)
            {
                src[i] = src[i+1];
            }
            src[i] = 0;
            return low;
         }
      }
    }
    return -1; //当low>high时表示查找区间为空，查找失败
} //BinSeareh

//二分插入法插入指定元素,前提是该队列未满,返回插入的位置
//此算法不严谨，有问题，1~15先插入奇数后插入偶数时，会产生，4排在5的后面，10排在11后面的问题(升序排列)。
int BinSearchInsert(unsigned short* src, unsigned char len,unsigned short key)
{ 
     unsigned char  i, low, high, mid,flag;
     if(src[len-1]!=0)//如果最后一个元素不空，说明队列已满
         return -1;
     //先确定非零元素表长
     while((len>1)&&(src[len-1]==0)) 
         len--;    
     low = 0;
     high = len-1; 

     if(key < src[low]) //如果比表头元素小，就插入到表头
     {
         for(i=len-1;i>low;i--)
         {
             src[i+1] = src[i];
         }
         src[i+1] = src[i];
         src[i] = key; 
         return low;
     }
     if(key > src[high])//如果比表尾元素大，就插入到表尾
     {
         if(src[high]!=0)
         {
            high++;           
         }
         src[high] = key;
         return high;
     } 
     
     while (low < high) // 在R[low...high]中折半查找有序插入的位置 
     {
                               
         mid = low + ((high-low)/2);// 找到中间元素  //使用 (low + high) / 2 会有整数溢出的问题
        
         if(key == src[mid])      //如果表内已经存在待插入的元素
            return mid;
        
         if (key < src[mid])      // 如果待插入的元素比中间元素前小，
         {
            high = mid-1;     //高界标前移
            flag = 0;
         }
         else                    // 如果待插入的元素比中间元素前大， 
         {
            low = mid+1;      //低界标后移
            flag = 1;
         }
     }
     //在low和high之间找到待插入元素的位置，需要将此位置后面的元素后移 
     for (i=len-1; i>high; i--)  // 元素后移 
     {   
           src[i+1] = src[i];             
     }
     //src[i+1] = src[i];
     if(flag)//高界标前移
         src[i] = key;
     else //低界标后移
         src[i+1] = key; // 插入
     return high;
        
}
//元素插入后按冒泡法排序，然后返回元素的序列号，失败返回-1。
int BubbleInsert(unsigned short* src, unsigned char len,unsigned short key)
{
    unsigned char  i,j, unchange;
    unsigned short tmp;
     if(src[len-1]!=0)//如果最后一个元素不空，说明队列已满
         return -1;
     if(key==0) 
         return -1;
     //先确定非零元素表长
     while((len>(unsigned char)1)&&(src[len-1]==0)) 
         len--;
     
     if(src[len-1] == 0)//如果该位置元素为0，说明此时表长为1
     {
         src[len-1] = key;
         return len-1;         
     }
     else
         len++;
     
     for(i=0;i<len-1;i++)
     {
         if(key == src[i])
            return (char)i;               
     }    
     src[i]=key;
         
     for (i=0; i<len; i++)
     {
        unchange = (unsigned char)1;
        for (j=0; j<len-1-i; j++)
        {
           if (src[j] > src[j+1])
           {
              unchange = 0;
              tmp = src[j];
              src[j] = src[j+1];
              src[j+1] = tmp;
           }
        }
        if (unchange == (unsigned char)1) //不再有变化，无需再排
        break;
     }
     for(i=0;i<len;i++)
     {
         if(key == src[i])
            return (char)i;               
     } 
     return (char)(-1);
}

//二分法获取索引元素，失败返回-1
int GetBinSearchValue(unsigned short *src, unsigned char len, unsigned char index)
{       
   unsigned char low,high, mid;//置当前查找区间上、下界的初值
   
   if(index > len-1) return -1;
 
   while((len>1)&&(src[len-1]==0)) len--;
   low = 0;
   high = len-1;
   if((src[index] < src[low])||(src[index] > src[high]))//元素不在次表中
       return -1;
   if(src[index] == src[low])
       return src[low];
   if(src[index] == src[high])
       return src[high];
   while(low < high)//当前查找区间R[low..high]非空
   {
      mid = low + ((high-low)/2); //使用 (low + high) / 2 会有整数溢出的问题
   
      if(src[index] == src[mid]) 
          return src[mid]; //查找成功返回
   
      if(src[index] < src[mid])
      {
         high = mid-1; //继续在R[low..mid-1]中查找
         if(src[index] == src[high])//如果上边界的元素正是要找的元素
             return src[high];
      }
      else
      {
         low = mid+1; //继续在R[mid+1..high]中查找
         if(src[index] == src[low])//如果下边界的元素正是要找的元素
             return src[low];
      }
    }
    return -1; //当low>high时表示查找区间为空，查找失败
} //BinSeareh

//获取升序有序表的最大值
int GetBubbleMaxValue(unsigned short *src, unsigned char len )
{       

   while((len>1)&&(src[len-1]==0)) len--;
   
    return src[len-1]; 
} 

//获取升序有序表的最大值的索引
int GetBubbleMaxIndex(unsigned short *src, unsigned char len )
{       

   while((len>1)&&(src[len-1]==0)) len--;
   
    return len-1; 
}



//----------------------------------------------------------------------------
//函数名称：rms(Root Mean Square)
//入口参数：unsigned int* pdata	指向源数据表的指针
//			unsigned char N	元素的个数
//返回参数: 0		所有元素均合法
//	    0xff	没有合法元素
//	    float       result    
//功能描述: 该函数实现对元素求均方根值	
//----------------------------------------------------------------------------

float rms(unsigned int* pdata,unsigned char N,unsigned char* err)
{
	unsigned char i = 0;
	double sum = 0;//32位浮点数
	float result = 0;

	if(N == 0)
	{
		*err = 0xff;
		return 0; 
	}
	else
	{
		for(i = 0;i < N;i++)
		{
			//先把指针变量转换成double型，再取其内容
			//sum += (long double)pow(*((double*)pdata),2);
			sum += (double)(((*(unsigned int*)pdata)*(*(unsigned int*)pdata))/N);
			pdata++;
		}
		
		result = (float)sqrt(sum);//再开方
		
		*err = 0;	
		return result;	
			
	}	
	
}	

//----------------------------------------------------------------------------
//函数名称：average
//入口参数：unsigned int* pdata	指向源数据表的指针
//			unsigned char N 元素的个数	
//返回参数: 0		所有元素均合法
//	    0xff	没有合法元素
//	    float       result    
//功能描述: 该函数实现对元素求满足精度要求的去除最大值和最小值的平均值	
//----------------------------------------------------------------------------
//extern OS_MEM *pMem_Comm;

float average(unsigned int* psrc,unsigned char N,unsigned char* err)
{
	//INT8U errMem_Get,errMem_Put;
	//INT16U *pdata;//声明一个源数据的拷贝
	unsigned int Mem_Comm[RCV_CAP_BUF_SIZE];
	
	unsigned char n = N;		 //保存元素的原始个数
	unsigned char i = 0;
	//unsigned int* pdata_dst= (unsigned int*)0;
	unsigned int elem_max = 0;
	unsigned int elem_min = 0;
	unsigned char pos_max = 0;
	unsigned char pos_min = 0;
	float sum_avg = 0;	//32位浮点数
	float sum_sqr = 0;	
	unsigned int* pdata_curr;//非法元素的当前位置	
	unsigned int* pdata_next;//非法元素的下一个位置	
	float toler_std = 0;
	
	unsigned int *pdata = Mem_Comm;
	unsigned int *pdst = Mem_Comm;

	//申请一块内存
	/*if (pMem_Comm != (OS_MEM*)0) //若内存创建成功
	{		
		pdata_dst = OSMemGet(pMem_Comm, &errMem_Get);
		if(errMem_Get == OS_NO_ERR)
		{
			//内存分配成功
			pdata = pdata_dst;
		}
		else if(errMem_Get == OS_MEM_NO_FREE_BLKS)
		{
			//没有内存分配
			*err = OS_MEM_NO_FREE_BLKS;
			return 0;//	
		}	
	}*/
	//内存分配成功后
	//把源数据的内容拷贝进新申请内存空间
	
	
	//pdata = pdata_dst;	
	for(i = 0;i < n;i++)
	{
		*pdata = *psrc; 
		pdata++;
		psrc++;	
	}
	//求列表中元素的均平差，来衡量元素在其中心位置波动的大小	
	while(1)
	{
		if(n == 0)
		{
			*err = 0xff;//没有合法数据
			sum_avg = 0;
			break;//goto Mem_Free;
		}			
		else
		{
			//求算术平均值
			pdata = pdst;//指针置表首
			sum_avg = 0;//平均值初始化为0	
			for(i = 0;i < n;i++)
			{
				sum_avg += (float)((float)(*pdata)/(float)n);
				pdata++;	
			}
			//求均方差(标准差)
			pdata = pdst;//指针置表首
			sum_sqr = 0;//平均值初始化为0
			for(i = 0;i < n;i++)
			{
				sum_sqr += ((float)(*pdata) - (sum_avg)) * ((float)(*pdata) - (sum_avg));
				pdata++;
			}
			toler_std = sqrt(sum_sqr/(n-1));
			
			//若公差不超标，就跳出循环
			if(((float)toler_std/(float)sum_avg) <= 0.1)
			{	
				*err = 0;			
				break;//goto Mem_Free;
			}
				
			pdata = pdst;//指针置表首	
			//否则就查找并去掉其最大值和最小值
			elem_max = pdata[0];//把最大值和最小值指向第一个元素
			elem_min = pdata[0];
			for(i = 0;i < n; i++)
			{
				if(elem_max <= pdata[i])
				{
					elem_max = pdata[i];
					pos_max = i;//记录最大元素位置
				}
				else if(elem_min >= pdata[i])
				{
					elem_min = pdata[i];
					pos_min = i;//记录最小元素位置
				}
				pdata++;
			}
			pdata = pdst;//指针置表首
			//去掉最大值
			pdata_curr = &pdata[pos_max];	//保存当前位置	
			pdata_next = &pdata[pos_max+1];	//指向当前位置的下一个元素位置
			for(i = 0;i < n-pos_max-1;i++)//删除找到的元素，把后的元素前移
			{				
				*pdata_curr = *pdata_next;//下一个元素前移
				pdata_curr++;
				pdata_next++;
			}
			n--;
			
			//去掉最小值
			pdata_curr = &pdata[pos_min];	//保存当前位置	
			pdata_next = &pdata[pos_min+1];	//指向当前位置的下一个元素位置
			for(i = 0;i < n-pos_min-1;i++)//删除找到的元素，把后的元素前移
			{				
				*pdata_curr = *pdata_next;//下一个元素前移
				pdata_curr++;
				pdata_next++;
			}
			n--;
							 
			if((float)((float)(N - n)/(float)N) > 0.5)//非法元素所占的比例
			{
				*err = 0xff;
				sum_avg = 0;
				break;//goto Mem_Free;
			}
		}					
	}
//Mem_Free:
	//释放内存空间
	//errMem_Put = OSMemPut(pMem_Comm, (void*)pdata_dst);
	//if(errMem_Put == OS_NO_ERR) 
	//{
		//内存释放成功		
	//}
	//else if(errMem_Put == OS_MEM_FULL)
	//{
		//内存区已经不能再接受更多释放的内存块。这种情况说明用户程序出现了错
		//误，释放了多于用OSMemGet（）函数得到的内存块。
		//挂起，等待释放内存
	//	while(1);
	//}		
	return (float)(sum_avg);//返回平均值
}

/* 加权递推平均滤波法 */ 
/*#define N 12
uint8_t code_coe[N] = {1,2,3,4,5,6,7,8,9,10,11,12};
uint8_t sum_coe = 1+2+3+4+5+6+7+8+9+10+11+12;
uint16_t filter()
{
    uint8_t count;
    uint16_t value_buf[N];
    uint32_t sum = 0;
    for(count = 0; count < N; count++)
    {
        value_buf[count] = ;
        
    }
    for(count =0; count < N; count++ )
    {
        sum += value_buf[count] * code_coe[count];
        
    }
    return (char)(sum/sum_coe);
}*/
