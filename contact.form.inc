<?php

/**
 * Contact Form
 *
 * @param $form
 * @param $form_state
 * @param null $id
 * @return mixed
 */
function contact_create_form($form, &$form_state, $id = NULL)
{
    if (!is_null($id)) {
        $contact = contact_fetch_individual_data($id);
        $form['id'] = [
            '#type' => 'hidden',
            '#default_value' => $id,
        ];
    }

    $form['firstname'] = [
        '#type' => 'textfield',
        '#title' => t('First Name'),
        '#required' => TRUE,
        '#default_value' => isset($contact->firstname) ? $contact->firstname : '',
    ];

    $form['lastname'] = [
        '#type' => 'textfield',
        '#title' => t('Last Name'),
        '#required' => TRUE,
        '#default_value' => isset($contact->lastname) ? $contact->lastname : '',
    ];

    $form['subject'] = [
        '#type' => 'textfield',
        '#title' => t('Subject'),
        '#required' => TRUE,
        '#default_value' => isset($contact->subject) ? $contact->subject : '',
    ];

    $form['message'] = [
        '#type' => 'textfield',
        '#title' => t('Message'),
        '#required' => TRUE,
        '#default_value' => isset($contact->message) ? $contact->message : '',
    ];

    $form['submit'] = [
        '#type' => 'submit',
        '#name' => 'save',
        '#value' => t('Save'),
    ];

    $form['cancel'] = [
        '#type' => 'submit',
        '#name' => 'cancel',
        '#value' => t('Cancel'),
    ];

    return $form;


}

/**
 * @param $id
 *
 * @return mixed
 * Fetch the individual contact data
 */
function contact_fetch_individual_data($id) {
    return db_select('contact', 'c')
        ->fields('c')
        ->condition('c.id', $id)
        ->execute()->fetchObject();
}