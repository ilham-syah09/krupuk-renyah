<?php
defined('BASEPATH') or exit('No direct script access allowed');

class Setting extends CI_Controller
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
        $this->load->model('M_admin');
    }

    public function index()
    {
        $this->db->order_by('id', 'desc');
        $setting = $this->db->get('setting', 1)->row();

        $data = [
            'title'     => 'Setting',
            'sidebar'   => 'admin/sidebar',
            'page'      => 'admin/setting',
            'setting'   => $setting
        ];

        $this->load->view('index', $data);
    }

    public function setSuhu()
    {
        $data = [
            'setSuhu'   => $this->input->post('setSuhu')
        ];

        $this->db->where('id', $this->input->post('id'));
        $this->db->update('setting', $data);
        $this->session->set_flashdata('toastr-success', 'berhasil');
        redirect('setting', 'refresh');
    }
}

/* End of file Monitoring.php */
