<?php
defined('BASEPATH') or exit('No direct script access allowed');

class Monitoring extends CI_Controller
{

    public function __construct()
    {
        parent::__construct();
        if (empty($this->session->userdata('log_admin'))) {
            $this->session->set_flashdata('toastr-eror', 'Anda Belum Login');
            redirect('auth', 'refresh');
        }

        $this->db->where('id', $this->session->userdata('id'));
        $this->dt_admin = $this->db->get('user')->row();
        $this->load->model('M_admin', 'admin');
    }

    public function index()
    {
        $data = [
            'title'     => 'Monitoring Nilai Sensor',
            'sidebar'   => 'admin/sidebar',
            'page'      => 'admin/monitoring',
            'monitor'   => $this->admin->getDataSensor()
        ];

        $this->load->view('index', $data);
    }
}

/* End of file Monitoring.php */
