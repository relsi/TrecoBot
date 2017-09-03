$(function(){

    var path = []; 

    $(".img-drag").draggable({
        helper: 'clone'
    });
    
    $(".direction-pad").droppable({
        drop: function(ev, ui) {
            $(this).html(ui.draggable.clone(true));
            var direction = $(ui.helper).data("direction");
            var position = $(this).data("position"); 
            path[position] = direction;
        }
    });

    $("#btn_start").on('click', function(){
       var directions = path;
       for (var i = 0; i < directions.length; i++) {
           var direction = directions[i];
            $.ajax({
                method: "GET",
                url: "http://192.168.1.102/move?dir="+direction
            });
           
       } 
    });

})