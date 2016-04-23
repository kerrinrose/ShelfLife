



function makeInterface(name, id, image) {
        
       var x = document.createElement("section");
       x.setAttribute("id", id);
         x.setAttribute("class", "item");
    document.getElementById("itemContainer").appendChild(x);
    
    var div = document.createElement("div");
    div.setAttribute("class", "absItem");
    x.appendChild(div);
    
    var paper = document.createElement("paper-material");
    paper.setAttribute("elevation", "1");
    div.appendChild(paper);
    
    var fresh = document.createElement("div");
    fresh.setAttribute("class", "freshMeterGreen");
    paper.appendChild(fresh);
    
    var inner = document.createElement("div");
    inner.setAttribute("class", "inner");
    paper.appendChild(inner);
    
     var img = document.createElement("img");
     img.setAttribute("src", image);
     inner.appendChild(img); 
    
    var span = document.createElement("span");
    inner.appendChild(span);
    
    
    var heading = document.createElement("H1");
    var txt1 = document.createTextNode(name);
    heading.appendChild(txt1);
    span.appendChild(heading);
    
    
    var i = 0;
$('.item').each(function() {

    i++;
    i = i%3;

    if (i == 1) $(this).addClass('left');  
    else if (i == 2) $(this).addClass('middle');
    else $(this).addClass('right');
  
  
  
});
         
         
         
    };
    
var ref = new Firebase("https://shelflife.firebaseio.com/reader");

    var uref = new Firebase("https://shelflife.firebaseio.com/userProducts");
    
    function populate() { //populate the interface to begin with
    uref.once("value", function(snapshot) {
        console.log("running begin function");
        
         snapshot.forEach(function(data) {
             var id = data.key();
             console.log("for each data: " + id);
              
             
             
        var itemref = new Firebase("https://shelflife.firebaseio.com/userProducts/"+id);
        
             itemref.once("value", function(snapshot) {
             var productData = snapshot.val();  
               var name = productData.Name;
                var image = productData.imageRef; 
              console.log(productData.expireDate);
              console.log(productData.imageRef);
                 
               makeInterface(name, id, image);
                 
                  
           });
             
             
             
         });
        
    });
        
    };
    

ref.on("child_added", function(snapshot) {
  var id = snapshot.val();
  console.log(id);
 
    ref.remove();
   

  uref.once("value", function(snapshot) {
      
       if(snapshot.child(id).exists()) {
           console.log("it exists, i'm removing it");

           var parent = document.getElementById("itemContainer");
var child = document.getElementById(id);
parent.removeChild(child);
          uref.child(id).remove();
          
           
       }
      
      
      else {
          
          console.log("not there, adding it");
          
          var pref = new Firebase("https://shelflife.firebaseio.com/products/"+id);
        
        
            pref.on("value", function(snapshot) {
          //    console.log("getting data");
            var productData = snapshot.val();
              console.log(productData.Name);
              console.log(productData.expireDate);
              console.log(productData.imageRef);
              
                var name = productData.Name; 
                var expire = productData.expireDate; 
                var image = productData.imageRef; 
              
        uref.child(id+"/Name").set(name);
        uref.child(id+"/expireDate").set(expire); 
        uref.child(id+"/imageRef").set(image);
                
               makeInterface(name,id, image);
          
              
          });
      }
      
      
      
  });
    
    
    
    
 
});
    



