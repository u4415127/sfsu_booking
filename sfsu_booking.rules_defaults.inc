<?php
/**
 * @file
 * sfsu_booking.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function sfsu_booking_default_rules_configuration() {
  $items = array();
  $items['rules_appointment_reminder'] = entity_import('rules_config', '{ "rules_appointment_reminder" : {
      "LABEL" : "Appointment Reminder",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_user_host" } }
            ],
            "DO" : [
              { "mail" : {
                  "to" : "[node:field-user-guest:mail]",
                  "subject" : "Appointment Reminder for [node:title]",
                  "message" : "This is a reminder for your appointment with [node:field-user-host:field-firstname] [node:field-user-host:field-firstname], [node:field-location], [node:field-time:value].",
                  "from" : "[node:field-user-host:mail]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Send appointment reminder"
          }
        }
      ]
    }
  }');
  $items['rules_book_time_slot'] = entity_import('rules_config', '{ "rules_book_time_slot" : {
      "LABEL" : "Book Appointment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "flag_flagged_appointment_booking" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "flagged-node" ],
            "type" : { "value" : { "appointment" : "appointment" } }
          }
        },
        { "data_is_empty" : { "data" : [ "flagged-node:field-user-guest" ] } },
        { "data_is" : {
            "data" : [ "flagged-node:field-time:value" ],
            "op" : "\\u003E",
            "value" : "now"
          }
        }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "flagged-node:field-status" ], "value" : "booked" } },
        { "flag_flagnode" : {
            "flag" : "appointment_booking",
            "node" : [ "flagged-node" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : 0
          }
        },
        { "redirect" : {
            "url" : "[site:url]comment\\/reply\\/[flagged-node:nid]##comment-form",
            "destination" : 1
          }
        },
        { "data_set" : {
            "data" : [ "flagged-node:field-user-guest" ],
            "value" : [ "site:current-user" ]
          }
        }
      ]
    }
  }');
  $items['rules_booking_expired_time_slot'] = entity_import('rules_config', '{ "rules_booking_expired_time_slot" : {
      "LABEL" : "Booking expired time slot",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "flag_flagged_appointment_booking" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "flagged-node" ],
            "type" : { "value" : { "appointment" : "appointment" } }
          }
        },
        { "data_is" : {
            "data" : [ "flagged-node:field-time:value" ],
            "op" : "\\u003C",
            "value" : "now"
          }
        }
      ],
      "DO" : [
        { "flag_unflagnode" : {
            "flag" : "appointment_booking",
            "node" : [ "flagged-node" ],
            "flagging_user" : "1",
            "permission_check" : 0
          }
        },
        { "component_rules_check_time_slot" : { "node" : [ "flagged-node" ] } },
        { "drupal_message" : {
            "message" : "Sorry, time slot [flagged-node:field-time:value] has expired. Please select another valid time slot.",
            "type" : "error"
          }
        }
      ]
    }
  }');
  $items['rules_cancel_appointment'] = entity_import('rules_config', '{ "rules_cancel_appointment" : {
      "LABEL" : "Cancel Appointment",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules_scheduler", "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "DO" : [
              { "schedule_delete" : { "component" : "rules_appointment_reminder", "task" : [ "node:nid" ] } }
            ],
            "LABEL" : "Clean-up"
          }
        },
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "entity_anonymous" : "Fetched Anonymous" } },
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              }
            ],
            "DO" : [
              { "entity_fetch" : {
                  "USING" : { "type" : "user", "id" : "0" },
                  "PROVIDE" : { "entity_fetched" : { "entity_anonymous" : "Fetched Anonymous" } }
                }
              },
              { "data_set" : { "data" : [ "node:field-status" ], "value" : "available" } },
              { "data_set" : { "data" : [ "node:field-user-guest" ], "value" : [ "0" ] } },
              { "data_set" : { "data" : [ "node:comment" ], "value" : "2" } },
              { "component_rules_remove_all_comments" : { "node" : [ "node" ] } }
            ],
            "LABEL" : "Re-open Time Slot"
          }
        }
      ]
    }
  }');
  $items['rules_cancel_appointment_by_flag'] = entity_import('rules_config', '{ "rules_cancel_appointment_by_flag" : {
      "LABEL" : "Cancel Appointment(Rule)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "flag_unflagged_appointment_booking" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "flagged-node" ],
            "type" : { "value" : { "appointment" : "appointment" } }
          }
        },
        { "OR" : [
            { "NOT data_is_empty" : { "data" : [ "flagged-node:field-user-guest" ] } },
            { "data_is" : {
                "data" : [ "flagged-node:field-user-guest" ],
                "value" : [ "flagging-user" ]
              }
            },
            { "data_is" : {
                "data" : [ "flagging-user" ],
                "value" : [ "flagged-node:field-user-host" ]
              }
            },
            { "user_has_role" : {
                "account" : [ "flagging-user" ],
                "roles" : { "value" : { "3" : "3", "6" : "6" } },
                "operation" : "OR"
              }
            }
          ]
        }
      ],
      "DO" : [
        { "drupal_message" : { "message" : "Appointment has been cancelled and a confirmation email has been sent to [flagged-node:field-user-guest:mail]." } },
        { "component_rules_cancel_appointment" : { "node" : [ "flagged-node" ] } },
        { "component_rules_send_booking_confirmation" : { "input_node" : [ "flagged-node" ] } }
      ]
    }
  }');
  $items['rules_check_time_slot'] = entity_import('rules_config', '{ "rules_check_time_slot" : {
      "LABEL" : "Check time slot and react",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "data_is_empty" : { "data" : [ "node:field-user-guest" ] } },
              { "data_is" : { "data" : [ "node:field-time:value" ], "op" : "\\u003C", "value" : "now" } }
            ],
            "DO" : [
              { "data_set" : { "data" : [ "node:field-status" ], "value" : "expired" } }
            ],
            "LABEL" : "Check and Close time slot"
          }
        }
      ]
    }
  }');
  $items['rules_remove_all_comments'] = entity_import('rules_config', '{ "rules_remove_all_comments" : {
      "LABEL" : "Remove all comments",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "entity_comment" : "Fetched comment" } },
            "DO" : [
              { "entity_query" : {
                  "USING" : { "type" : "comment", "property" : "node", "value" : [ "node" ] },
                  "PROVIDE" : { "entity_fetched" : { "entity_comment" : "Fetched comment" } }
                }
              },
              { "LOOP" : {
                  "USING" : { "list" : [ "entity-comment" ] },
                  "ITEM" : { "list_item_comment" : "Current list item comment" },
                  "DO" : [ { "entity_delete" : { "data" : [ "list-item-comment" ] } } ]
                }
              }
            ],
            "LABEL" : "Remove all comments (rule)"
          }
        }
      ]
    }
  }');
  $items['rules_remove_appointment_time_slot'] = entity_import('rules_config', '{ "rules_remove_appointment_time_slot" : {
      "LABEL" : "Remove Appointment Time Slot and Notify Guest",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag", "rules_scheduler" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "flag_flagged_node" : {
                  "flag" : "appointment_booking",
                  "node" : [ "node" ],
                  "flagging_user" : [ "node:author" ]
                }
              }
            ],
            "DO" : [
              { "mail" : {
                  "to" : [ "node:field-user-guest:mail" ],
                  "subject" : "Appointment Canceled: [node:title]",
                  "message" : "Your appointment is cancelled by host. To reschedule appointment, please follow the link and select a time.\\r\\n[site:url]booking\\/cal\\r\\n\\r\\nIf you have any questions, please reply to this message.",
                  "from" : [ "node:field-user-host:mail" ],
                  "language" : [ "" ]
                }
              },
              { "drupal_message" : { "message" : "Cancellation notice has been sent to [node:field-user-guest:mail]" } }
            ],
            "LABEL" : "Send Cancel Notice"
          }
        },
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "flag_flagged_node" : {
                  "flag" : "appointment_booking",
                  "node" : [ "node" ],
                  "flagging_user" : [ "site:current-user" ]
                }
              }
            ],
            "DO" : [
              { "schedule_delete" : { "component" : "rules_appointment_reminder", "task" : [ "node:nid" ] } }
            ],
            "LABEL" : "Clean-up"
          }
        },
        { "RULE" : {
            "DO" : [ { "entity_delete" : { "data" : [ "node" ] } } ],
            "LABEL" : "Cancel Appointment"
          }
        }
      ]
    }
  }');
  $items['rules_schedule_time_slot_management'] = entity_import('rules_config', '{ "rules_schedule_time_slot_management" : {
      "LABEL" : "Schedule time slot management",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "rules_scheduler", "views_bulk_operations" ],
      "ACTION SET" : [
        { "schedule" : {
            "component" : "rules_schedule_time_slot_management",
            "date" : "now +10 min",
            "identifier" : "node_expire"
          }
        },
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "list_of_time_slots_to_check|page" },
            "PROVIDE" : { "entity_list" : { "entity_list" : "list of time slots" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "entity-list" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [ { "component_rules_check_time_slot" : { "node" : [ "list-item" ] } } ]
          }
        }
      ]
    }
  }');
  $items['rules_send_booking_confirmation'] = entity_import('rules_config', '{ "rules_send_booking_confirmation" : {
      "LABEL" : "Send appointment confirmation",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag" ],
      "USES VARIABLES" : { "input_node" : { "label" : "Input Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "input-node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "flag_flagged_node" : {
                  "flag" : "appointment_booking",
                  "node" : [ "input-node" ],
                  "flagging_user" : [ "site:current-user" ]
                }
              }
            ],
            "DO" : [
              { "mail" : {
                  "to" : [ "input-node:field-user-guest:mail" ],
                  "subject" : "Appointment Comfirmation for [input-node:title]",
                  "message" : "Thank you for using our online calendar to schedule your appointment with Young Kim, Tax Specialist at San Francisco State University.\\r\\nThis email confirms your appointment on [input-node:field-time:value].\\r\\nMs. Kim is located in the Administration Building in [input-node:field-location].\\r\\nFor any questions, please email yskim@sfsu.edu\\r\\n\\r\\nTo cancel the appointment, please follow the link and click on \\u0022Cancel appointment.\\u0022\\r\\n[input-node:url]\\r\\n\\r\\nImportant\\r\\nWhen coming to the appointment:\\r\\nA.  If Employment related bring the following documents:\\r\\n    1. Social Security Number\\r\\n    2. Passport page showing name, number and photo\\r\\n    3. U.S. Visa\\r\\n    4. Form I-94 \\u201cArrival \\u0026 Departure Record\\u201c (small white card inside your passport)\\r\\n    5. Form I-20 or DS-2019 (primary purpose)\\r\\n    6. If you are a student, obtain Employment Eligibility Verification form (EEV) from Financial Aid Office at SSB One Stop \\r\\n        Employment Eligibility Verification form - http:\\/\\/fiscaff.sfsu.edu\\/fiscalaffairs\\/files\\/forms\\/pdf\\/SFSU%20FNI_0104_rev%20090110_0.pdf\\r\\nB.  If Renewal of job on campus or a new or different job, bring a new Employment Eligibility Verification for each new job and any updated documents.\\r\\nC.  If Financial Aid Hold related bring documents requested in the email letter you received. The Foreign National Information Form must be completed prior to meeting the tax specialist along with bringing copies of the above documentation.\\r\\n",
                  "from" : [ "input-node:field-user-host:mail" ],
                  "language" : [ "" ]
                }
              },
              { "mail" : {
                  "to" : "[input-node:field-user-host:mail]",
                  "subject" : "Appointment: [input-node:title]",
                  "message" : "You have an appointment on [input-node:field-time:value]\\r\\n[input-node:url]",
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Send booking confirmation"
          }
        },
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "input-node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "NOT flag_flagged_node" : {
                  "flag" : "appointment_booking",
                  "node" : [ "input-node" ],
                  "flagging_user" : [ "site:current-user" ]
                }
              }
            ],
            "DO" : [
              { "mail" : {
                  "to" : "[input-node:field-user-host:mail]",
                  "subject" : "Appointment Cancellation",
                  "message" : "Appointment \\u0022[input-node:title]\\u0022 has been cancelled.\\r\\n[input-node:url]",
                  "from" : "[input-node:field-user-host:mail]",
                  "language" : [ "" ]
                }
              },
              { "mail" : {
                  "to" : [ "input-node:field-user-guest:mail" ],
                  "subject" : "Appointment Cancellation for [input-node:title]",
                  "message" : "Your appointment is cancelled.  To reschedule appointment, please follow the link below and select a new time.\\r\\n[site:url]booking\\/cal",
                  "from" : [ "input-node:field-user-host:mail" ],
                  "language" : [ "" ]
                }
              }
            ],
            "LABEL" : "Send Cancel Confirmation"
          }
        }
      ]
    }
  }');
  $items['rules_slot_duplicate'] = entity_import('rules_config', '{ "rules_slot_duplicate" : {
      "LABEL" : "Slot Duplicate",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : {
              "variable_added" : { "new_time" : "New Time" },
              "entity_created" : { "entity_node_created" : "Created node" }
            },
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_time" } },
              { "NOT data_is_empty" : { "data" : [ "node:field-time" ] } }
            ],
            "DO" : [
              { "variable_add" : {
                  "USING" : {
                    "type" : "date",
                    "value" : {
                      "select" : "node:field-time:value",
                      "date_offset" : { "value" : 604800 }
                    }
                  },
                  "PROVIDE" : { "variable_added" : { "new_time" : "New Time" } }
                }
              },
              { "entity_create" : {
                  "USING" : {
                    "type" : "node",
                    "param_type" : "appointment",
                    "param_title" : "[node:field-user-host:name] - [new-time:short]",
                    "param_author" : [ "site:current-user" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_node_created" : "Created node" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-user-host" ],
                  "value" : [ "node:field-user-host" ]
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-time" ],
                  "value" : [ "node:field-time" ]
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-time:value" ],
                  "value" : {
                    "select" : "node:field-time:value",
                    "date_offset" : { "value" : 604800 }
                  }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-node-created:field-time:value2" ],
                  "value" : {
                    "select" : "node:field-time:value2",
                    "date_offset" : { "value" : 604800 }
                  }
                }
              }
            ],
            "LABEL" : "Copy time slot to next week"
          }
        }
      ]
    }
  }');
  $items['rules_slot_reserve'] = entity_import('rules_config', '{ "rules_slot_reserve" : {
      "LABEL" : "Slot Reserve",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules", "flag", "rules_scheduler", "comment" ],
      "ON" : { "comment_insert" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "appointment" : "appointment" } }
          }
        }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "comment:node:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_node" : "Fetched node" } }
          }
        },
        { "data_set" : {
            "data" : [ "comment:node:field-user-guest" ],
            "value" : [ "comment:author" ]
          }
        },
        { "data_set" : { "data" : [ "comment:node:comment" ], "value" : "1" } },
        { "data_set" : { "data" : [ "comment:node:field-status" ], "value" : "booked" } },
        { "data_set" : { "data" : [ "comment:status" ], "value" : "1" } },
        { "flag_flagnode" : {
            "flag" : "appointment_booking",
            "node" : [ "entity-node" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : 0
          }
        },
        { "component_rules_send_booking_confirmation" : { "input_node" : [ "comment:node" ] } },
        { "schedule" : {
            "component" : "rules_appointment_reminder",
            "date" : {
              "select" : "comment:node:field-time:value",
              "date_offset" : { "value" : -86400 }
            },
            "identifier" : [ "comment:node:nid" ],
            "param_node" : [ "comment:node" ]
          }
        },
        { "drupal_message" : { "message" : "Appointment with [entity-node:field-user-host:name] on [entity-node:field-time:value] has been reserved and a confirmaion email has been sent to [comment:node:field-user-guest:mail]." } }
      ]
    }
  }');
  $items['rules_slot_reset'] = entity_import('rules_config', '{ "rules_slot_reset" : {
      "LABEL" : "Re-open Time Slot",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "TAGS" : [ "sfsu_booking" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "Node", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_fetched" : { "entity_anonymous" : "Fetched Anonymous" } },
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "node" ],
                  "type" : { "value" : { "appointment" : "appointment" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_user_guest" } }
            ],
            "DO" : [
              { "entity_fetch" : {
                  "USING" : { "type" : "user", "id" : "0" },
                  "PROVIDE" : { "entity_fetched" : { "entity_anonymous" : "Fetched Anonymous" } }
                }
              },
              { "data_set" : { "data" : [ "node:field-status" ], "value" : "available" } },
              { "data_set" : { "data" : [ "node:field-user-guest" ], "value" : [ "0" ] } },
              { "data_set" : { "data" : [ "node:comment" ], "value" : "2" } },
              { "component_rules_remove_all_comments" : { "node" : [ "node" ] } }
            ],
            "LABEL" : "Re-open Time Slot"
          }
        }
      ]
    }
  }');
  return $items;
}
