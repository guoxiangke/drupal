(function ($) {

  Drupal.tabbed_room_selector = {};

  Drupal.tabbed_room_selector.getRrule = function(form_data, room_id, start_date, start_time, end_time) {
    dates = new Array();

    //process repeating dates first
    ajax_endpoint = Drupal.settings.basePath+'tabbed_room_selector_convert_rrule';
    $.ajax({
      url: ajax_endpoint,
      dataType: 'json',
      data: form_data,
      fieldRoomNid: room_id,
      fieldStartDate: start_date,
      room_id: room_id,
      start_date: start_date,
      start_time: start_time,
      end_time: end_time,
      success: function(data, textStatus, jqXHR) {
        dates = data.dates;
        // console.log(dates);
        if(dates.length) {
          for(i in dates) {
            Drupal.tabbed_room_selector.checkConflict(this.room_id, dates[i], this.start_time, this.end_time);
          }
        } else {
          Drupal.tabbed_room_selector.checkConflict(this.room_id, this.start_date, this.start_time, this.end_time);
        }
      },
      beforeSend: function() {
        //remove previous conflict message of this checkbox
        $('input[name="field_room[und]['+this.fieldRoomNid+']"]').siblings('.conflict').remove();
        //add loading gif
        $('#edit-field-room label[for=edit-field-room-und]').after('<div id="ajax-progress-'+this.fieldRoomNid+'-'+this.fieldStartDate+'" class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      },
      complete: function() {
        //remove loading gif
        $('#ajax-progress-'+this.fieldRoomNid+'-'+this.fieldStartDate).remove();
      }
    });
  }
  Drupal.tabbed_room_selector.checkConflict = function(room_id, start_date, start_time, end_time) {
    ajax_endpoint = Drupal.settings.basePath+'reservations';
    $.ajax({
      url: ajax_endpoint,
      dataType: 'json',
      // data: $('form#reservation-node-form').serialize(),
      data: {
        'field_date_value2[value][date]': start_date,
        'field_date_value2[value][time]': end_time,
        'field_date_value[value][date]': start_date,
        'field_date_value[value][time]': start_time,
        'field_room_nid': room_id,
        'field_room_target_id': room_id,
      },
      fieldRoomNid: room_id,
      fieldStartDate: start_date,
      success: function(data, textStatus, jqXHR) {
        // console.log(data);
        for (i in data) {
          //there is a conflict
          conflict = data[i];
          node_link = Drupal.settings.basePath+'node/'+conflict.nid;
          user_link = Drupal.settings.basePath+'user/'+conflict.users_node_uid;

          //ignore conflict with itself (in edit case)
          var intRegex = /^\d+$/;
          if(intRegex.test(Drupal.settings.tabbed_room_selector.arg[1])) {
            if(conflict.nid == Drupal.settings.tabbed_room_selector.arg[1]) {
              continue;
            }
          }

          date_markup = '';
          for(i in conflict.field_field_date) {
            date_markup += conflict.field_field_date[i].rendered['#markup']+' ';
          }

          $('input[name="field_room[und]['+this.fieldRoomNid+']"]').parent().append('<div class="conflict"><span class="error">Conflict</span>'+
            ' <strong class="user"><a target="_blank" href="'+node_link+'">'+conflict.node_title+'</a></strong>'+
            ' (<a target="_blank" href="'+user_link+'">'+conflict.users_node_name+'</a>) booked '+
            '<strong>'+date_markup+'</strong></div>');

          //in conflict, deselect it
          $('input[name="field_room[und]['+this.fieldRoomNid+']"]').attr('checked', false);
          $('.need-approval input').removeAttr('disabled');
        }

      },
      beforeSend: function() {
        //remove previous conflict message of this checkbox
        $('input[name="field_room[und]['+this.fieldRoomNid+']"]').siblings('.conflict').remove();
        //add loading gif
        $('#edit-field-room label[for=edit-field-room-und]').after('<div id="ajax-progress-'+this.fieldRoomNid+'-'+this.fieldStartDate+'" class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      },
      complete: function() {
        //remove loading gif
        $('#ajax-progress-'+this.fieldRoomNid+'-'+this.fieldStartDate).remove();
      }
    }); //end ajax
  }

  // Re-enable form elements that are disabled for non-ajax situations.
  Drupal.behaviors.disableOtherRequireApprovalRooms = {
    attach: function(context, settings) {

      //onload show tabs
      $('#edit-field-room-und .views-field-field-resource-category .field-content').each(function(){
        form_item = $(this).parents('.form-item:eq(0)').detach();
        $('.group-floor-'+$(this).html()).find('.fieldset-wrapper').prepend(form_item);
        $(this).hide();
      });
      $('.views-field-field-resource-catogory').hide();
      $('.views-field-field-resource-category').hide();

      htabs = $('.group-rooms').detach();
      $('#edit-field-room-und').html(htabs);

      //onload hide need approval
      $('.views-field-field-need-approval .field-content:not(:empty)').parents('.form-type-checkbox').addClass('need-approval');

      //onload disable other need approval if there is already one
      if($('#edit-field-room-und .need-approval input:checked').length) {
        $('#edit-field-room-und .need-approval input:not(:checked)').attr('disabled', 'disabled');
        $('#edit-field-resource .need-approval input:not(:checked)').attr('disabled', 'disabled');
      }

      $('#edit-field-resource-und input', context).once('resourceSingleApproval', function(){
        $(this).change(function(){

          /*
          4 types of events
          3. click approval room - check conflick, disable other approval checkbox
          4. unclick approval room - enable other approval checkbox
          */

          if($(this).parents('.form-item').hasClass('need-approval')) {
            //there is a checkbox with approval, case 3
            if($(this).attr('checked')) {
              $('.need-approval input:not(:checked)').attr('disabled', 'disabled');
            } else {
              //there is no approval room, case 4
              $('.need-approval input').removeAttr('disabled');
            }
          }
        });
      });

      $('#checkall', context).once('checkall', function(){
        $(this).click(function(){

          $('#edit-field-room-und input').each(function(){
            room_id = $(this).val();
            start_date = $('form#reservation-node-form input[name="field_date[und][0][value][date]"]').val();
            start_time = $('form#reservation-node-form input[name="field_date[und][0][value2][time]"]').val();
            end_time = $('form#reservation-node-form input[name="field_date[und][0][value][time]"]').val();
            form_data = $('form#reservation-node-form').serialize();

            new Drupal.tabbed_room_selector.getRrule(form_data, room_id, start_date, start_time, end_time);
            
          });

          return false;
        });
      });

      $('#edit-field-date input, #edit-field-date select', context).once('dateChange', function(){
        $(this).change(function(){
          $('#edit-field-room-und input:checked').each(function(){
            room_id = $(this).val();
          
            if(room_id) {
              start_date = $('form#reservation-node-form input[name="field_date[und][0][value][date]"]').val();
              start_time = $('form#reservation-node-form input[name="field_date[und][0][value2][time]"]').val();
              end_time = $('form#reservation-node-form input[name="field_date[und][0][value][time]"]').val();
              form_data = $('form#reservation-node-form').serialize();

              new Drupal.tabbed_room_selector.getRrule(form_data, room_id, start_date, start_time, end_time);
            }
          });
        });
      });

      //on click "need approval" room to check booking conflict
      $('#edit-field-room-und input', context).once('checkconflict', function(){
        $(this).change(function(){
          
          /*
          4 types of events
          1. click normal room - check conflick
          2. unclick normal room = do nothing
          3. click approval room - check conflick, disable other approval checkbox
          4. unclick approval room - enable other approval checkbox
          */

          if($(this).parents('.form-item').hasClass('need-approval')) {
            //there is a checkbox with approval, case 3
            if($(this).attr('checked')) {
              $('.need-approval input:not(:checked)').attr('disabled', 'disabled');
            } else {
              //there is no approval room, case 4
              $('.need-approval input').removeAttr('disabled');
            }
          }


          //check conflict no matter approval or not
          if($(this).attr('checked')){

            room_id = $(this).val();
            start_date = $('form#reservation-node-form input[name="field_date[und][0][value][date]"]').val();
            start_time = $('form#reservation-node-form input[name="field_date[und][0][value2][time]"]').val();
            end_time = $('form#reservation-node-form input[name="field_date[und][0][value][time]"]').val();
            form_data = $('form#reservation-node-form').serialize();

            new Drupal.tabbed_room_selector.getRrule(form_data, room_id, start_date, start_time, end_time);

          } //end if checked

        });

      });
    }
  }

})(jQuery);
