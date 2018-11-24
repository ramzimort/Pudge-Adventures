jQuery(function() {
	
	/* EDITOR */
	
	/* Drag&Drop that snaps to grid */
	
	var dragging = false;
	
	jQuery("#grid .editor_element").draggable({ containment: "#grid", start: function() { dragging = true; }, drag: function() { dragging = true; }, stop: function() { dragging = false; } });
	
	/* Remove Element */
	
	jQuery("#grid").on("click", ".editor_element .remove", function() {
		jQuery(this).parent().remove();
	});
	
	/* Add element */
	
	jQuery(".edit_add").click(function() {
		var newObj = '<div class="editor_element new_element ' + jQuery(this).attr('data-class') + '" data-prefab="' + jQuery(this).attr('data-prefab') + '"' +
			' style="position: absolute;left: ' + (jQuery('#grid').width()/2 - jQuery(this).attr('data-halfwidth') * 1)  + 'px; top: ' + (jQuery('#grid').height()/2 - jQuery(this).attr('data-halfheight') * 1)  + 'px;"' +
			' data-halfwidth="' + jQuery(this).attr('data-halfwidth') + '" data-halfheight="' + jQuery(this).attr('data-halfheight') + '" data-scale="' + jQuery(this).attr('data-scale') + '">' +
			'<div class="remove">+</div></div>';
			if(jQuery(this).attr("data-z") > 0) {
				 jQuery("#grid").append(newObj);
			}else{
				 jQuery("#grid").prepend(newObj);
			}
		jQuery("#grid .editor_element.new_element").draggable({	containment: "#grid", start: function() { dragging = true; }, drag: function() { dragging = true; }, stop: function() { dragging = false; } }).removeClass('new_element');
	});
	
	/* Save to textarea */
	
	jQuery("#edit_save").click(function() {
		var i = 0;
		
		var levelFile = '';
		jQuery('#grid').children().each(function() {
			var posX = parseFloat(jQuery(this).css("left"), 10)/1.0 + parseFloat(jQuery(this).attr("data-halfwidth")) - jQuery('#grid').width()/2.0;
			var posY = -1*(parseFloat(jQuery(this).css("top"), 10)/1.0 + parseFloat(jQuery(this).attr("data-halfheight")) - jQuery('#grid').height()/2.0);
			var newElem = '\t\t{\n\t\t\t"Name": "' + jQuery(this).attr('data-prefab') + '",';
			newElem += '\n\t\t\t"PosX" : ' + posX + ',\n\t\t\t"PosY" : ' + posY + '\n\t\t},\n';
			levelFile = newElem + levelFile;
			i++;
		});
		
		jQuery('#result').html(levelFile);
	});
	
	/* Select all text when clicking on textarea */
	
	jQuery('#result').focus(function() {
		jQuery(this).select();
	});
	
	/* Load from filename */
	/*
	$('#button_load').click(function(e) {
		var filename = jQuery('#load_filename').val();
		
		if(filename != '') {
		
			jQuery.ajax({
				url: filename + '.json',
				beforeSend: function(xhr){
					if (xhr.overrideMimeType) {
						xhr.overrideMimeType("application/json");
					}
				},
				dataType: "json",
				type: 'get',
				success: function(data) {
					loadLevel(data);
					alert("Level " + filename + " loaded!");
					jQuery('#load_filename').val('');
					jQuery('#result').html('');
				},
				error: function() {
					alert("ERROR - File does not exist");
				}
			});
		
		}else{
			alert("Please insert a filename");
		}
    });
	*/
	/* Decode json object */
	/*
	function loadLevel(data) {
		// Load Level Info
		jQuery('#level_name').val(data.name);
		jQuery('#next_level').val(data.next_level);
		jQuery('#add_weapon').val(data.add_weapon);
		jQuery('#level_background').val(data.background);
		jQuery('#music_track').val(data.music_track);
		
		// Empty Grid
		jQuery("#grid").html('');
		
		jQuery.each(data.objects, function() {
			
			var obj = jQuery(this)[0];
			
			var splitting = obj.prefab.split('/');
			prefabname = splitting[splitting.length - 1];
			
			if(obj.prefab == "player1") {
				var pos_left = (obj.overrides.positionX - 4) * 32;
				var pos_top = -1 * (obj.overrides.positionY - 25) * 32;
				
				jQuery("#grid").append(
				'<div class="editor_element elem_4x4 player01" data-prefab="player1" style="left: ' + pos_left + 'px; top: ' + pos_top + 'px;"' +
				' data-halfwidth="2" data-halfheight="2" data-2p="0"></div>');
			}else if(obj.prefab == "player2") {
				var pos_left = (obj.overrides.positionX - 4) * 32;
				var pos_top = -1 * (obj.overrides.positionY - 25) * 32;
				
				jQuery("#grid").append(
				'<div class="editor_element elem_4x4 player02" data-prefab="player2" style="left: ' + pos_left + 'px; top: ' + pos_top + 'px;"' +
				' data-halfwidth="2" data-halfheight="2" data-2p="1"></div>');
			}else{
				var classes = jQuery('#element-' + prefabname).attr('data-class');
				var halfwidth = jQuery('#element-' + prefabname).attr('data-halfwidth');
				var halfheight = jQuery('#element-' + prefabname).attr('data-halfheight');
				
				var pos_left = (obj.overrides.positionX - 2 - halfwidth) * 32;
				var pos_top = -1 * (obj.overrides.positionY - 27 + parseFloat(halfheight, 10)) * 32;
				
				var asd = '<div class="editor_element ' + classes + '" data-prefab="' + obj.prefab + '"' +
				' data-halfwidth="' + halfwidth + '" data-halfheight="' + halfheight + '" data-2p="0" style="left: ' + pos_left + 'px; top: ' + pos_top + 'px;">' +
				'<div class="remove">+</div></div>';
				
				jQuery("#grid").append(asd);
			}
			
		});
		
		jQuery("#grid .editor_element").draggable({ containment: "#grid", start: function() { dragging = true; }, drag: function() { dragging = true; }, stop: function() { dragging = false; } });
		
	}
	*/
	/* Scroll to Center of grid on load */
	
	jQuery(window).load(function(m){
		jQuery(window).scrollTop(jQuery('#grid').height()/2 - jQuery(window).height()/2); 
		jQuery(window).scrollLeft(jQuery('#grid').width()/2 - jQuery(window).width()/2 + 320);
	});
	
	/* SCROLLING FROM CODEPEN */
	
	var curDown = false,
		curYPos = 0,
		curXPos = 0;
		
	$(window).mousemove(function(m){
		if(!dragging) {
			if(curDown === true){
				$(window).scrollTop($(window).scrollTop() + (curYPos - m.pageY)); 
				$(window).scrollLeft($(window).scrollLeft() + (curXPos - m.pageX));
			}
		}
	});
  
	$(window).mousedown(function(m){
			curDown = true;
			curYPos = m.pageY;
			curXPos = m.pageX;
	});
  
	$(window).mouseup(function(){
		curDown = false;
	});
	
});