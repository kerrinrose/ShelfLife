<script src="https://cdn.firebase.com/js/client/2.4.2/firebase.js"></script>

var ref = new Firebase("https://shelflife.firebaseio.com/");


ref.on("child_added", function(snapshot) {
  var idScan = snapshot.val();
  console.log("Author: " + idScan);
 
 
});