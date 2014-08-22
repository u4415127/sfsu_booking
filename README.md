sfsu_booking
============

SFSU booking is a Drupal feature that implements an appointment booking and management system.


DEPENDENCIES
---------------------

* auto_nodetitle
* calendar
* comment
* context
* ctools
* date
* date_api
* date_ical
* date_popup
* features 7.x-2.x
* flag 7.x-2.x (not compatible with 3.x branch)
* list
* page_manager
* panels
* rules
* rules_scheduler
* strongarm
* token
* user_reference
* views
* views_bulk_operations
* views_content
* views_ui

INSTALLATION
---------------------

* Install as a feature as usual, see http://drupal.org/node/70151 for further information.

* After feature activation you'll get:
  - node type 'appointment';
  - 4 views -- Calendar, Time slot info, Guest Info, and a view for rules scheduler
  - taxonomy 'booking status';
  - role 'Host';
  - varius rules to process appointments.


USAGE
---------------------

* User with 'Host' role can create a new appointment slot and manage them in the calendar's page.
* Registered user can book an appointment from the calendar page.


CONTACT
---------------------


Current maintainers:
* YingLuan Tan - Alan.YL.Tan@gmail.com
* Supakit Kiatrungrit - supakitk@sfsu.edu
* Srikanth Danapal - srikanth@sfsu.edu


This project has been sponsored by:
* SFSU - San Francisco State University
  Visit http://www.sfsu.edu for more information.


