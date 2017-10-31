#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int ascending;    //1 if array is sorted in ascending order, 0 if descending
int key;          //the key to be searched for, in the array
int matched_index = -1 ;       //index of the matched key



typedef enum {
        LessThan = 0,
        LessThanEquals = 1,
        Equals = 2,
        GreaterThanEquals = 3,
        GreaterThan = 4
} SearchType;

typedef enum {
        NotFound,
        FoundExact,
        FoundGreater,
        FoundLess
} SearchResult;

SearchType type;
SearchResult result;

//generating the strings for the enums
const char* getTypeString(SearchType type)
{
	switch(type){
		case LessThan: return "LessThan";
		case LessThanEquals: return "LessThanEquals";
		case Equals: return "Equals";
		case GreaterThanEquals: return"GreaterThanEquals";
		case GreaterThan: return "GreaterThan";
	}
}

const char* getResultString(SearchResult result)
{
	switch(result){
		case NotFound: return "NotFound";
		case FoundExact: return "FoundExact";
		case FoundGreater: return "FoundGreater";
		case FoundLess: return "FoundLess";
	}
}

SearchResult Search(
  const int * const items,
  const int n_items,
  const int ascending,
  const int key,
  const SearchType type,
  int* const index)
{
	int i,j,lessflag=0, equalstoflag=0,greaterthanflag=0;
      matched_index = -1;

  switch(type)
  {

////////////////////// Equals Case ///////////////////////

    		case Equals:{
    			for(i=0;i<n_items;i++){
    				if(key ==*(items+i))
    				{
    					equalstoflag++;
    					matched_index=i;
    					break;
    				}
    				else continue;
    			}

    			if(equalstoflag == 0)
              return NotFound;
    			else
              return FoundExact;
    		}
//////////////////// Greater Than Case //////////////////

        		case GreaterThan:
            {
            if(ascending!=0)
            {
                 if(key >= items[n_items-1]) //Checking if key is >= last element in an ascending array
                 {

                     greaterthanflag=2;
                     matched_index = -1 ;

                 }
                 else
                    {
                        for(i=0;i<n_items-1;i++)
                        {
                          if(key >= *(items+i) && key < *(items+i+1))
                                  {
                                      greaterthanflag++;
                                      matched_index = i+1;
                                      break;
                                  }
                          else continue;
                        }
                        if(greaterthanflag == 0)
                        {
                        greaterthanflag = 1;
                        matched_index = 0;
                        }
                    }
        		}
            // checking descending array below
        		else
            {
        			if(key >= *(items+0))
                  {
                      greaterthanflag=2;
                      matched_index = -1;
                  }
              else if(key < items[n_items-1])
                  {
                    greaterthanflag++;
                    matched_index = n_items-1;
                  }
             	else{
                    for(i=1;i<n_items;i++)
                    {
                        if(key >= *(items+i) && key < *(items+i-1))
                            {
                                greaterthanflag++;
                                matched_index = i-1;
                                break;
                            }
                        else continue;
                    }
                  }
        		}
            //printf("%d",greaterthanflag);
            if (greaterthanflag==2) return NotFound;
            else return FoundGreater;
            }

///////////////// GreaterThanEquals Case /////////////////

      case GreaterThanEquals:{
                  equalstoflag=0, greaterthanflag=0;
    //checking equals case below
        for(i=0;i<n_items;i++)
              {
              if(key==*(items+i))
                    {
                         equalstoflag++;
                         matched_index = i;

                         break;
                    }
              else continue;
              }
      if(ascending!=0)
      {

  //checking greater than case below
      if(key>*(items+n_items-1)) // checking last element of acending array
          greaterthanflag=0;
      else
          {
            for(i=0;i<n_items-1;i++)
             {      if (key < items[0]) {
                    greaterthanflag++;
                    matched_index=0;
             }
                    else if(key >= *(items+i) && key < *(items+i+1))
                    {
                       if(equalstoflag == 1)
                       {
                         return FoundExact;
                       }
                       greaterthanflag++;
                       matched_index=i+1;

				               break;
                    }
                    else continue;
              }
          }
      }
    // checking descending array below
      else
      {
      	if(key>*(items+0))
          {  greaterthanflag=0;
            matched_index = -1;
          }
        else if (key < items[n_items-1])
            {
              greaterthanflag++;
              matched_index = n_items-1;
            }
        else{
              for(i=1;i<n_items;i++)
              {
                if(key > *(items+i) && key < *(items+i-1))
                      {
                        greaterthanflag++;
                        matched_index=i-1;
                        break;
                      }
                      else continue;
              }
            }
      }
      if (equalstoflag!=0)
          return FoundExact;
      else if(greaterthanflag!=0)
          return FoundGreater;
      else
          return NotFound;
      }
///////////////////// Less Than Case ///////////////////////
		case LessThan:
    {
		if(ascending!=0)
    {
			if(key < *(items+0)) //checking if first element is less than key
      {
        lessflag=0;
      }
      else if(key > items[n_items-1]){
        lessflag++;
        matched_index = n_items - 1;

      }
  		else
      {
				for(i=0;i<n_items;i++){
					if(key <= *(items+i) && key > *(items+i-1))
					{
						lessflag++;
						matched_index = i-1;
						break;
					}
					else continue;
				}
			}
		}
    // checking descending array below
		else
    {
			if(key < *(items+n_items-1))
            {
              lessflag=0;
              matched_index = -1;
            }
      else if(key > items[0])
          {
            lessflag++;
            matched_index = 0;
          }
      else
          {
              for(i=0;i<n_items-1;i++)
              {
                      if(key <= *(items+i) && key > *(items+i+1))
                      {
                              lessflag++;
                              matched_index = i+1;
                              break;
                      }
                      else continue;
              }
          }

		}
		if (lessflag==0)
      return NotFound;
    else
      return FoundLess;
		}
//////////////////// Less Than Equals Case ///////////////////

		case LessThanEquals:{
		equalstoflag=0,
    lessflag=0;
    // checking equals to key condition below
    for(i=0;i<n_items;i++)
        {
          if(key == *(items+i))
          {
            equalstoflag++;
            matched_index = i;
            //printf("%d\n",matched_index );
            if (equalstoflag!=0)
               return FoundExact;
            break;
          }
          else continue;
        }
		if(ascending!=0)
    {

      // checking less than key condition below
			if(key<*(items+0))
          {
            lessflag=0;
          }
      else if (key > items[n_items-1])
          {
                  lessflag++;
                  matched_index = n_items-1;

          }
			else
        {
    				for(i=1;i<n_items;i++)
            {
    					if(key < *(items+i) && key > *(items+i-1))
    					{
    						lessflag++;
    						matched_index = i-1;
                //printf("%d\n",matched_index );
    						break;
    					}
    					else continue;
    				}
  			}
		}
    //check for descending array
		else
    {
			if(key<*(items+n_items-1))
          {
            lessflag=0;
            matched_index = -1 ;
          }
      else if(key>items[0])
            {
              lessflag++;
              matched_index = 0;
            }

      else
            {
                for(i=0;i<n_items-1;i++)
                {
                        if(key <= *(items+i) && key > *(items+i+1))
                        {
                                lessflag++;
                                matched_index = i+1;
                                break;
                        }
                        else continue;
                }
            }
		}
	 	if (equalstoflag!=0)
        return FoundExact;
    else if(lessflag!=0)
        return FoundLess;
    else
        return NotFound;
		}



	}
}

static void test_ascending()
{
  //_____________ Test Cases for Ascending Array___________________//

  printf("\n\nTesting Ascending array [0,2,4,6,8]\n");
  printf("+-----+-------------------+--------------+-------+ \n | Key | Type              | Returns      | Index | \n+-----+-------------------+--------------+-------+\n");

        int items_ascending[] ={0,2,4,6,8};
        result = Search(items_ascending,5,1,key=-1,type=LessThanEquals,&matched_index);
        printf("   %d    %s      %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=0,type=LessThan,&matched_index);
        printf("    %d    %s            %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=0,type=Equals,&matched_index);
        printf("    %d    %s              %s      %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=1,type=Equals,&matched_index);
        printf("    %d    %s              %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=2,type=GreaterThanEquals,&matched_index);
        printf("    %d    %s   %s      %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=2,type=GreaterThan,&matched_index);
        printf("    %d    %s         %s    %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=-1,type=GreaterThan,&matched_index);
        printf("   %d    %s         %s    %d\n",key,getTypeString(type),getResultString(result),matched_index);
        result = Search(items_ascending,5,1,key=10,type=LessThan,&matched_index);
        printf("    %d   %s            %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);


}

static void test_descending()
{
  //__________________Test cases for Descending array__________________//

  printf("\n\nTesting Descending array [8,6,4,2,0]\n");
  printf("+-----+-------------------+--------------+-------+ \n | Key | Type              | Returns      | Index | \n+-----+-------------------+--------------+-------+\n");

          int items[] ={8,6,4,2,0};
          result = Search(items,5,0,key=-1,type=LessThan,&matched_index);
          printf("   %d    %s            %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=4,type=LessThanEquals,&matched_index);
          printf("    %d    %s      %s      %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=8,type=Equals,&matched_index);
          printf("    %d    %s              %s      %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=5,type=GreaterThanEquals,&matched_index);
          printf("    %d    %s   %s    %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=2,type=GreaterThanEquals,&matched_index);
          printf("    %d    %s   %s      %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=9,type=GreaterThan,&matched_index);
          printf("    %d    %s         %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=10,type=LessThan,&matched_index);
          printf("    %d   %s            %s       %d\n",key,getTypeString(type),getResultString(result),matched_index);
          result = Search(items,5,0,key=-1,type=GreaterThan,&matched_index);
          printf("   %d    %s         %s    %d\n\n",key,getTypeString(type),getResultString(result),matched_index);

}

static void test_ascending_using_assert()
    {

      int *items = (int *)malloc(sizeof(int) * 8);
      int i = 0;
      for (i = 0; i < 8; i++)
          items[i] = i*2; // [0,2,4,6,8,10,12,14]

      matched_index = -1;

      assert(Search(items, 8, 1, -1, Equals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 19, Equals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 0 , Equals, &matched_index) == FoundExact);
      assert(matched_index == 0);

      matched_index = -1;
      assert(Search(items, 8, 1, 13 , GreaterThan, &matched_index) == FoundGreater);
      assert(matched_index == 7);

      matched_index = -1;
      assert(Search(items, 8, 1, 14 , GreaterThan, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 17 , GreaterThanEquals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 14 , GreaterThanEquals, &matched_index) == FoundExact);
      assert(matched_index == 7);

      matched_index = -1;
      assert(Search(items, 8, 1, -1 , GreaterThanEquals, &matched_index) == FoundGreater);
      assert(matched_index == 0);

      matched_index = -1;
      assert(Search(items, 8, 1, -2 , LessThan, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 0 , LessThan, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 1 , LessThan, &matched_index) == FoundLess);
      assert(matched_index == 0);

      matched_index = -1;
      assert(Search(items, 8, 1, 16 , LessThan, &matched_index) == FoundLess);
      assert(matched_index == 7);

      matched_index = -1;
      assert(Search(items, 8, 1, -3 , LessThanEquals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 8, 1, 14 , LessThanEquals, &matched_index) == FoundExact);
      assert(matched_index == 7);

      matched_index = -1;
      assert(Search(items, 8, 1, 16 , LessThanEquals, &matched_index) == FoundLess);
      assert(matched_index == 7);

      free(items);

      printf("All tests for Ascending array using Assert succeeded.\n");
    }

static void test_descending_using_assert()
    {
      int *items = (int *)malloc(sizeof(int) * 20);
      int j = 20;
      for (int i = 0; i < 10; i++)
      {
        items[i] = j ; // [20,18,16,14,....,2]
        j = j-2;
      }

      matched_index = -1;
      assert(Search(items, 10, 0, -1, Equals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 10, 0, 19, Equals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 10, 0, 2 , Equals, &matched_index) == FoundExact);
      assert(matched_index == 9 );

      matched_index = -1;
      assert(Search(items, 10, 0, 20 , GreaterThan, &matched_index) == NotFound);
      assert(matched_index == -1 );

      matched_index = -1;
      assert(Search(items, 10, 0, 17 , GreaterThan, &matched_index) == FoundGreater);
      assert(matched_index == 1 );

      matched_index = -1;
      assert(Search(items, 10, 0, 21 , GreaterThanEquals, &matched_index) == NotFound);
      assert(matched_index == -1 );

      matched_index = -1;
      assert(Search(items, 10, 0, 20 , GreaterThanEquals, &matched_index) == FoundExact);
      assert(matched_index == 0);

      matched_index = -1;
      assert(Search(items, 10, 0, 1 , GreaterThanEquals, &matched_index) == FoundGreater);
      assert(matched_index == 9);

      matched_index = -1;
      assert(Search(items, 10, 0, 2, LessThan, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 10, 0, 3 , LessThan, &matched_index) == FoundLess);
      assert(matched_index == 9);

      matched_index = -1;
      assert(Search(items, 10, 0, 1 , LessThanEquals, &matched_index) == NotFound);
      assert(matched_index == -1);

      matched_index = -1;
      assert(Search(items, 10, 0, 4 , LessThanEquals, &matched_index) == FoundExact);
      assert(matched_index == 8);

      matched_index = -1;
      assert(Search(items, 10, 0, 21 , LessThanEquals, &matched_index) == FoundLess);
      assert(matched_index == 0);

      free(items);

      printf("All tests for Descending array using Assert succeeded.\n\n");
    }
int main()
{

/* Assumptions
    * ---------------------------------------------
    *  The Input array will be sorted
    *  Items will be non-NULL
    *  There are no duplicate items
    *  n_items will be > 0
    *  If key not found index = -1 will be returned
    * ----------------------------------------------
*/

test_ascending();
test_descending();
test_ascending_using_assert();
test_descending_using_assert();
}
