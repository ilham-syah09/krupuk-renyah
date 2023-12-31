<?php
defined('BASEPATH') or exit('No direct script access allowed');

class Admin extends CI_Controller
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
            'title'         => 'Dashboard',
            'sidebar'       => 'admin/sidebar',
            'page'          => 'admin/dashboard',
        ];

        $this->load->view('index', $data);
    }

    public function realtime()
    {
        $this->db->order_by('id', 'desc');
        $query = $this->db->get('sensor', 1)->row();

        echo json_encode($query);
    }
}

/* End of file Admin.php */
