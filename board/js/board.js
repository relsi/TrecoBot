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
       alert(path); 
    });

})