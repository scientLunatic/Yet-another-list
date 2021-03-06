# Yet-another-list
Fancy list for rushing through all your data structure needs... that other implementations probably can do better.

<h3>Full spec:</h3> <ul><li>Doubly linked</li> 
               <li>Holds void*<sup>(so just consider it a reference list)</sup></li>
               <li>Doesn't clear references so you can work with unallocated variables<br> but allocated memory needs to be freed by hand<sup>(I shouldn't have to tell you that but warnings are a fair way to avoid unecessary trouble)</sup></li>
               <li>Circular on both ends</li>
               <li>Also works both by using a new allocated list<sup>(that then also requires freeing)</sup> or just a plain variable.</li>
               <li><b>About seeking:</b></li><ul>
                  <li>Any index is fine</li>
                  <li>List starts at 0</li>
                  <li>Indexes that surpass the list length will wrap around<br><i>So for a list of size 2, index 1, 3, 5, . . . , 2n + 1 will all land at the second item</i></li>
                  <li>Indexes smaller than zero track backwards</li>
                  <li>Index 0 has special behaviour when needed, refering to the head pointer specifically and not just the first node</li>
               </ul>
               <li>Has queue and stack macros</li>
               <li>No dubiously helpful encapsulation<sup>(or as C goes, I assume you know what you're doing)</sup> so everything is visible like the list's length and node structure</li>
               <li><b>About the operations</b></li><ul>
                  <li><b>new_yalist :</b> allocate zeroed list</li>
                  <li><i>Prepend yal<sup>(yet another list)</sup> to everything.</i></li>
                  <li><b>add :</b> add node with ref<sup>(0 pushes to head)</sup></li>
                  <li><b>rem :</b> frees & removes node</li>
                  <li><b>edit :</b> edit node</li>
                  <li><b>find :</b> check for node existence, returns success, and if true, sets "index" to the index of the referencing node</li>
                  <li><b>get :</b> returns reference</li>
                  <li><b>take :</b> gets and removes</li>
                  <li><b>clear :</b> removes every node, leaves list and doesn't free any references</li>
                  <li><i>Also prepend no<sup>(node)</sup> to the next two</i></li>
                  <li><b>fetch :</b> fetch node using index rules</li>
                  <li><b>set :</b> quick node set</li>
                  <li><i>only macros ahead</i></li>
                  <li><b>push</b> </li>
                  <li><b>pop</b> </li>
                  <li><b>enqueue</b> </li>
                  <li><b>dequeue</b> </li>
               </ul>
             </ul><br>  
<h3>Usage :</h3>

```C
    YALIST* listpointer = new_yalist(), plainlist = {NULL, 0};
    
    int numbers[10], *dynnums = malloc(10 * sizeof(int));//yes, they will have garbage. The more disorderly the merrier
    int i;
    
    
    //adding, indexing, ordering & pointer-reference interchangeability
    for(i = 0; i < 10; i++)
      {
        yaladd(listpointer, &numbers[i],  0); //equivalent to push, list becomes inverted in relation to array
        yaladd( &plainlist, dynnums + i, -1); //equivalent to enqueue, list stays relative to memory pointed by "dynnums"
      }
      
      
    //access
    yalfind(&plainlist, dynnums, &i);//try to find first int in dynnums on plainlist
    printf("%d = %d\n", dynnums[0], *(int*)yalget(&plainlist, i)); //should be equal
    
    yalclear(listpointer);                                  //reset list
    printf("%d\n", yalfind(listpointer, &numbers[0], NULL));//fail finding
    
    int answer = 42;
    yaledit(&plainlist, 0, &answer);         //change first from dynnums to &answer
    
    yalpush(listpointer, yalpop(&plainlist));//throw into the other list
    printf("%d\n", *(int*)yalget(listpointer, 0));  //lo and behold there it is (is it?)
    
    
    //finish
    while(plainlist.length)
        yalpush(listpointer, yalpop(&plainlist));
        
    while(listpointer->length)
        printf("%d\n", *(int*)yalpop(listpointer));
        
    free(listpointer);
    free(dynnums);
 ```
