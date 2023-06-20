<?php
defined('BASEPATH') or exit('No direct script access allowed');

class M_admin extends CI_Model
{

    public function getDataSensor()
    {
        $this->db->order_by('id', 'desc');
        return $this->db->get('sensor')->result();
    }
}

/* End of file M_admin.php */
