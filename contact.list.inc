<?php


/**
 * Get Contact list
 *
 * @return mixed
 */
function contact_list() {
    $form['contacts'] = [
        '#theme' => 'table',
        '#header' => getContactHeader(),
        '#rows' => getContactRows(),
        '#empty' => t('No contacts available.'),
    ];

    $form['pager']['#markup'] = theme('pager');
    return $form;
}

/**
 * Get Contact Rows
 *
 * @return array
 */
function getContactRows()
{
    global $base_url;

    $query = db_select('contact', 'c')
        ->fields('c');
    $query = $query->extend('PagerDefault')
        ->extend('TableSort')
        ->orderByHeader(getContactHeader());
    $query->limit(5);
    $contacts = $query->execute()->fetchAll();

    $rows = [];
    foreach ($contacts as $contact) {
        $view_link = l(t('View'), $base_url . '/contacts/' . $contact->id . '/details');
        $edit_link = l(t('Edit'), $base_url . '/contacts/' . $contact->id . '/edit');
        $delete_link = l(t('Delete'), $base_url . '/contacts/' . $contact->id . '/delete');

        $rows[] = [
            'id' => ['data' => $contact->id],
            'fname' => ['data' => $contact->firstname],
            'lname' => ['data' => $contact->lastname],
            'subject' => ['data' => $contact->subject],
            'operation' => ['data' => $view_link . '&nbsp;&nbsp;&nbsp;' . $edit_link . '&nbsp;&nbsp;&nbsp;' . $delete_link],
        ];
    }

    return $rows;
}


/**
 * Get Contact Header
 *
 * @return array
 */
function getContactHeader()
{
    return [
        'id' => ['data' => t('Id'), 'field' => 'c.id'],
        'fname' => ['data' => t('First Name'), 'field' => 'c.firstname'],
        'lname' => ['data' => t('Last Name'), 'field' => 'c.lastname'],
        'subject' => ['data' => t('Subject'), 'field' => 'c.subject'],
        'operation' => ['data' => t('Actions')],
    ];
}